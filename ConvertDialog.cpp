

#include "ConvertDialog.h"

ConvertDialog::ConvertDialog(QWidget *parent):QDialog(parent)
{
    cm = new ConversionManager(this);
    convertDialogSettings = new QSettings("K&K", "Hong", this);

    setupUi();
    setupConnections();
    setupLayout();

    setWindowTitle(tr("Convert"));
}

ConvertDialog::ConvertDialog(QWidget *parent, const QString &filePath)
    :QDialog(parent),inputPath(filePath)
{

}

void ConvertDialog::setupUi()
{
    formatCombo = new QComboBox;
    formatCombo->addItems(QStringList() << "mp3" << "wav" << "flac");

    qualityCombo = new QComboBox;
    qualityCombo->addItem("High", QVariant("high"));
    qualityCombo->addItem("Medium", QVariant("medium"));
    qualityCombo->addItem("Low", QVariant("low"));

    sourcePathEdit = new QLineEdit;
    sourcePathEdit->setReadOnly(true);

    QString lastUsedDir = convertDialogSettings->value("lastDir",
                                                       QDir::homePath()).toString();



    destPathEdit = new QLineEdit;
    destPathEdit->setText(lastUsedDir);

    btnChoseDest = new QPushButton("Choose Destination");

    btnConvert = new QPushButton("Convert");
    btnOpenDir = new QPushButton("Open Directory");
    btnOpenDir->setEnabled(false);


    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);

}

void ConvertDialog::setupConnections()
{
    connect(btnChoseDest,&QPushButton::clicked,this,[=]() {

        QString lastDir = convertDialogSettings->value("lastDir", QDir::homePath()).toString();

        QString dir = QFileDialog::getExistingDirectory(this,
                                                        tr("Open Directory"),lastDir,
         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if(!dir.isEmpty()) {

            destPathEdit->setText(dir);

            convertDialogSettings->setValue("lastDir", dir);
        }
    });

    connect(btnConvert,&QPushButton::clicked, this,&ConvertDialog::onConvert);
    connect(btnOpenDir,&QPushButton::clicked,this,&ConvertDialog::onOpenDirectory);

    connect(cm,&ConversionManager::conversionStarted,this,[this]() {
        btnConvert->setDisabled(true);
        btnOpenDir->setDisabled(true);
    });

    connect(cm,&ConversionManager::conversionFinished,
            this,[this](bool success,const QString &outputPath) {
        if(success) {
            QMessageBox::information(this,tr("Conversion"),tr("Conversion Succeeded"));
            currentOutputPath = outputPath;
            btnOpenDir->setEnabled(true);
            btnConvert->setEnabled(true);
        } else {
            QMessageBox::critical(this,tr("Conversion"),tr("Conversion Failed"));
        }
    });

    // connect(formatCombo,&QComboBox::currentTextChanged,this,&ConvertDialog::onFormatChanged);
    connect(cm,&ConversionManager::conversionProgressUpdated,this,[this](double progress) {
        progressBar->setValue(static_cast<int>(progress));
    });
}

void ConvertDialog::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(new QLabel("Format:"));
    layout->addWidget(formatCombo);

    layout->addWidget(new QLabel("Quality:"));
    layout->addWidget(qualityCombo);

    layout->addWidget(new QLabel("Source Path:"));
    layout->addWidget(sourcePathEdit);

    layout->addWidget(new QLabel("Desination Path"));
    layout->addWidget(destPathEdit);

    layout->addWidget(btnChoseDest);
    layout->addWidget(btnConvert);
    layout->addWidget(btnOpenDir);

    layout->addWidget(progressBar);

    setLayout(layout);
}

void ConvertDialog::setSourcePath(const QString &filePath)
{
    sourcePathEdit->setText(filePath);
}

void ConvertDialog::onConvert()
{

    QString srcPath = sourcePathEdit->text();

    QString destPath = destPathEdit->text() +
                       "/" + QFileInfo(srcPath).baseName() + "." + formatCombo->currentText();

    convertDialogSettings->setValue("lastDir", QFileInfo(destPath).absolutePath());
    // QString format = formatCombo->currentText();
    // QString quality = qualityCombo->currentData().toString();
    // currentOutputPath = destPath;
    qDebug() << "Selected quality:" << qualityCombo->currentData().toString();
    cm->convert(srcPath, destPath, formatCombo->currentText(),
                qualityCombo->currentData().toString());
}

void ConvertDialog::onOpenDirectory()
{
    QDir dir = QFileInfo(currentOutputPath).absoluteDir();

    QDesktopServices::openUrl(QUrl::fromLocalFile(dir.absolutePath()));
}





