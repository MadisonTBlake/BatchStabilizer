#ifndef TASKS_BASE_H
#define TASKS_BASE_H

#include "action_result.h"

#include <QObject>
#include <QProcess>

class TasksBase : public QObject
{
    Q_OBJECT
private:

    QProcess *m_Proc;

public:



    enum TasksTypes
    {
        DESHAKER_PASS1,
        DESHAKER_PASS2,
        MPEG_CONVERSION
    };

    TasksBase() :
        m_Proc(NULL)
    {

    }

    void Abort() {
        if(m_Proc != NULL) {
            m_Proc->terminate();
            CleanAfterAbort();
        }
    }

    virtual TasksTypes Type() const = 0;

    virtual void Execute() = 0;

    virtual bool Equal(const TasksBase &that) = 0;

    virtual void CleanAfterAbort() = 0;

    virtual bool ShouldIgnoreFile(const QString &filename) = 0;

    virtual QString Output() const = 0;

protected:
    void Execute(const QString &command)
    {
        if(m_Proc != NULL) {
            throw std::runtime_error("Attempting to execute a task already being performed");
        }

        m_Proc = new QProcess();
        QString str = "M:\\VirutalDub\\vdub.exe /i Deshaker_Pass1.vcf \"M:\\Videos\\Test\\GOPR0292-1\" \"mp4\"";
        m_Proc->start(command);
        connect(m_Proc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(ProcessFinished(int,QProcess::ExitStatus)));
    }

signals:

    void Done(TasksBase *, ActionResult) const;

private slots:

    void ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
    {
        delete m_Proc;
        m_Proc = NULL;

        if(exitStatus == QProcess::NormalExit) {
            emit Done(this, ActionResult());
        }
        else {
            emit Done(this, ActionResult("Some Error Encountered"));
        }


    }
};


#endif // TASKS_BASE_H
