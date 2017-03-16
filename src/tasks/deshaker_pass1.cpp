#include "deshaker_pass1.h"

#include <QFileInfo>
#include <QDir>
#include <QThread>

DeshakerPass1::DeshakerPass1(const QString &VDubPath, const QString &filename) :
    DeshakerGeneric(VDubPath, filename)
{

}

DeshakerPass1::~DeshakerPass1()
{
    Abort();
}

DeshakerPass1::TasksTypes DeshakerPass1::Type() const
{
    return TasksBase::DESHAKER_PASS1;
}

void DeshakerPass1::Execute()
{
    QFileInfo info(this->m_Filename);
    TasksBase::Execute(this->m_VDubPath.replace("/", "\\") + "\\vdub.exe /i Deshaker_Pass1.vcf \"" + info.absoluteDir().absolutePath().replace("/", "\\") + "\\" + info.completeBaseName() + "\" \"" + info.completeSuffix() + "\"");
}

bool DeshakerPass1::Equal(const TasksBase &that)
{
    if(this->Type() != that.Type()) {
        return false;
    }

    const DeshakerPass1& that_obj = (const DeshakerPass1&)that;

    if(this->m_Filename != that_obj.m_Filename) {
        return false;
    }

    if(this->m_VDubPath != that_obj.m_VDubPath) {
        return false;
    }

    return true;
}

void DeshakerPass1::CleanAfterAbort()
{
    QProcess killProc;
    killProc.start("taskkill /im VirtualDub.exe /f");
    killProc.waitForFinished();
    QThread::msleep(500);

    QFileInfo info(this->m_Filename);
    QFile::remove(info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + ".log");
}

bool DeshakerPass1::ShouldIgnoreFile(const QString &filename)
{
    QFileInfo f1(filename);

    QFileInfo info(this->m_Filename);
    QFileInfo f2(info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + ".log");

    if(f1 == f2) {
        return true;
    }
    return false;
}

QString DeshakerPass1::Output() const
{
    QFileInfo info(this->m_Filename);
    return info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + ".log";
}
