#ifndef DESHAKER_PASS1_H
#define DESHAKER_PASS1_H

#include "deshaker_generic.h"

class DeshakerPass1 : public DeshakerGeneric
{
private:

public:

    DeshakerPass1(const QString &VDubPath, const QString &filename);

    ~DeshakerPass1();

    virtual TasksTypes Type() const;

    virtual void Execute();

    virtual bool Equal(const TasksBase &that);

    virtual void CleanAfterAbort();

    virtual bool ShouldIgnoreFile(const QString &filename);

    virtual QString Output() const;
};

#endif // DESHAKER_PASS1_H
