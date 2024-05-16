

#include "ConversionManager.h"


ConversionManager::ConversionManager(QObject *parent):QObject(parent)
{

}

void ConversionManager::convert(const QString &srcPath, const QString &targetPath,
                                const QString &format,const QString &quality)

{

    double duration = getFileDuration(srcPath);

    QProcess *process = new QProcess(this);



    QStringList arguments;
    arguments << "-y" << "-i" << srcPath;

    // Customize FFmpeg command based on format
    if(format == "mp3") {
        arguments << "-codec:a" << "libmp3lame";
        if(quality == "high") {
            arguments << "-qscale:a" << "2";
        } else if(quality == "medium") {
            arguments << "-qscale:a" << "5";
        } else {
            arguments << "-qscale:a" << "9";
        }
    } else if(format == "wav") {

        // For WAV, you might adjust sample rate or bit depth here, if needed
        // For example, setting CD quality sample rate and bit depth
        if(quality == "high") {
            arguments << "-ar" << "44100" << "-ac" << "2" << "-b:a" << "1411k";
        } else if(quality == "medium") {
            arguments << "-ar" << "22050" << "-ac" << "2" << "-b:a" << "705k";
        } else {
            arguments << "-ar" << "11025"  << "-ac" << "1" << "-b:a" << "352k";
        }

    } else if(format == "flac") {

        if(quality == "high") {
            arguments << "-compression_level" << "8";
        } else if(quality == "medium" ){
            arguments << "-compression_level" << "5";
        } else {
            arguments << "-compression_level" << "0";
        }


        // arguments << "-c:a" << "flac";
    }

    arguments << targetPath;

    connect(process, &QProcess::readyReadStandardError, [this,process,duration]() {
        // QString stderrOutput = process->readAllStandardError();
        QByteArray stderrOutput = process->readAllStandardError();
        QString output(stderrOutput);

        int timeIndex = output.indexOf("time=");

        if (timeIndex != -1) {
            int start = timeIndex + 5; // Start of the time value, skipping "time="
            int end = output.indexOf(" ", start); // End of the time value, assuming it ends with a space
            if (end == -1) end = output.length(); // If no space found, assume end of string
            QString timeString = output.mid(start, end - start);

            // Now split the timeString by ':' to get hours, minutes, and seconds
            QStringList timeParts = timeString.split(':');
            if (timeParts.size() >= 3) {
                double hours = timeParts.at(0).toDouble();
                double minutes = timeParts.at(1).toDouble();
                double seconds = timeParts.at(2).toDouble();

                double currTime = hours * 3600 + minutes * 60 + seconds;


                double progress = (currTime / duration) * 101;

                emit conversionProgressUpdated(progress);
            }
        }
        // QRegularExpression regex("time=(\\d+):(\\d+):(\\d+\\.\\d+)");
        // QRegularExpressionMatch match = regex.match(output);

        // if(match.hasMatch()) {
        //     double hours = match.captured(1).toInt();
        //     double minutes = match.captured(2).toInt();
        //     double seconds = match.captured(3).toDouble();
        //     double currTime = (hours * 3600) + (minutes*60) + seconds;

        //     double progress = (currTime / duration) * 101;

        //     emit conversionProgressUpdated(progress);
        // }

    });

    connect(process,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, process, targetPath](int exitCode, QProcess::ExitStatus) {
        if(exitCode == 0) {
            emit conversionFinished(true, targetPath);
        }

        process->deleteLater();
    });

    process->start("ffmpeg", arguments);
    qDebug() << "process->start";
    emit conversionStarted();
}



double ConversionManager::getFileDuration(const QString &filePath)
{
    QProcess ffprobeProcess;
    ffprobeProcess.start("ffprobe", QStringList() << "-v" << "error" << "-show_entries"
                            <<"format=duration" << "-of" << "default=noprint_wrappers=1:nokey=1"
                                                  << filePath);

    ffprobeProcess.waitForFinished();
    QByteArray output = ffprobeProcess.readAllStandardOutput();

    return output.trimmed().toDouble();
}






















