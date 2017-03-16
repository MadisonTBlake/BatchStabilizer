#include "deshaker_pass2.h"

#include <QFileInfo>
#include <QDir>
#include <QThread>

DeshakerPass2::DeshakerPass2(const QString &VDubPath, const QString &filename) :
    DeshakerGeneric(VDubPath, filename)
{

}

DeshakerPass2::~DeshakerPass2()
{
    Abort();
}

DeshakerPass2::TasksTypes DeshakerPass2::Type() const
{
    return TasksBase::DESHAKER_PASS2;
}

void DeshakerPass2::Execute()
{
    QFileInfo info(this->m_Filename);
    TasksBase::Execute(this->m_VDubPath.replace("/", "\\") + "\\vdub.exe /i Deshaker_Pass2.vcf \"" + info.absoluteDir().absolutePath().replace("/", "\\") + "\\" + info.completeBaseName() + "\" \"" + info.completeSuffix() + "\"");
}

bool DeshakerPass2::Equal(const TasksBase &that)
{
    if(this->Type() != that.Type()) {
        return false;
    }

    const DeshakerPass2& that_obj = (const DeshakerPass2&)that;

    if(this->m_Filename != that_obj.m_Filename) {
        return false;
    }

    if(this->m_VDubPath != that_obj.m_VDubPath) {
        return false;
    }

    return true;
}

void DeshakerPass2::CleanAfterAbort()
{
    QProcess killProc;
    killProc.start("taskkill /im VirtualDub.exe /f");
    killProc.waitForFinished();
    QThread::msleep(500);

    QFileInfo info(this->m_Filename);
    QFile::remove(info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + "_stabalized.avi");
}

bool DeshakerPass2::ShouldIgnoreFile(const QString &filename)
{
    QFileInfo f1(filename);

    QFileInfo info(this->m_Filename);
    QFileInfo f2(info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + "_stabalized.avi");

    if(f1 == f2) {
        return true;
    }
    return false;
}

QString DeshakerPass2::Output() const
{
    QFileInfo info(this->m_Filename);
    return info.absoluteDir().absolutePath() + QDir::separator() + info.completeBaseName() + "_stabalized.avi";
}
