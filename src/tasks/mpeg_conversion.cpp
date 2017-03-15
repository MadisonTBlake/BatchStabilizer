#include "mpeg_conversion.h"

#include <QFileInfo>
#include <QDir>

MPEGConversion::MPEGConversion(const QString &ffmpegPath, const QString &filename) :
    m_Filename(filename),
    m_FFMPEGPath(ffmpegPath)
{

}

MPEGConversion::~MPEGConversion()
{
    Abort();
}

QString MPEGConversion::Filename() const {
    return m_Filename;
}

QString MPEGConversion::FFMPEGPath() const {
    return m_FFMPEGPath;
}

MPEGConversion::TasksTypes MPEGConversion::Type() const
{
    return TasksBase::MPEG_CONVERSION;
}

void MPEGConversion::Execute()
{
    QFileInfo info(this->m_Filename);
    QString in = info.absoluteDir().absolutePath().replace("/", "\\") + "\\" + info.completeBaseName() + "." + info.completeSuffix();
    QString out = info.absoluteDir().absolutePath().replace("/", "\\") + "\\" + info.completeBaseName() + ".mp4";
    QString command = this->FFMPEGPath().replace("/", "\\") + "\\ffmpeg.exe -i " + in + " -c:a aac -b:a 128k -c:v libx264 -crf 23 " + out;
    TasksBase::Execute(command);
}

bool MPEGConversion::Equal(const TasksBase &that)
{
    if(this->Type() != that.Type()) {
        return false;
    }

    const MPEGConversion& that_obj = (const MPEGConversion&)that;

    if(this->m_Filename != that_obj.m_Filename) {
        return false;
    }

    if(this->m_FFMPEGPath != that_obj.m_FFMPEGPath) {
        return false;
    }

    return true;
}

void MPEGConversion::CleanAfterAbort()
{
    QFileInfo info(this->m_Filename);
    QFile::remove(info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + "_stablized.mp4");
}

bool MPEGConversion::ShouldIgnoreFile(const QString &filename)
{
    QFileInfo f1(filename);

    QFileInfo info(this->m_Filename);
    QFileInfo f2(info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + "_stablized.mp4");

    if(f1 == f2) {
        return true;
    }
    return false;
}

QString MPEGConversion::Output() const
{
    QFileInfo info(this->m_Filename);
    return info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + "_stablized.mp4";
}
