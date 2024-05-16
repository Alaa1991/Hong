#ifndef CONVERTDIALOG_H
#define CONVERTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QDir>
#include <QString>
#include <QDesktopServices>
#include "ConversionManager.h"
#include <QProgressBar>
#include <QSettings>

class ConvertDialog : public QDialog {
    Q_OBJECT

public:
    explicit ConvertDialog(QWidget *parent=nullptr);
    explicit ConvertDialog(QWidget *parent, const QString &filePath);

    void setSourcePath(const QString &filePath);

private slots:
    void onConvert();
    void onOpenDirectory();
    // void onFormatChanged();
private:
    void setupUi();
    void setupConnections();
    void setupLayout();

    void startConversion(const QString &sourcePath, const QString &targetPath,
                         const QString &format);

    QString inputPath;
    QString currentOutputPath;
    QComboBox *formatCombo;
    QLineEdit *sourcePathEdit;
    QLineEdit *destPathEdit;
    QPushButton *btnConvert;
    QPushButton *btnOpenDir;
    QPushButton *btnChoseDest;

    QComboBox *qualityCombo;

    ConversionManager *cm;
    QProgressBar *progressBar;
    QSettings *convertDialogSettings;
};



#endif // CONVERTDIALOG_H


