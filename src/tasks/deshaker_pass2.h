#ifndef DESHAKER_PASS2_H
#define DESHAKER_PASS2_H

#include "deshaker_generic.h"

class DeshakerPass2 : public DeshakerGeneric
{
private:

public:

    DeshakerPass2(const QString &VDubPath, const QString &filename);

    ~DeshakerPass2();

    virtual TasksTypes Type() const;

    virtual void Execute();

    virtual bool Equal(const TasksBase &that);

    virtual void CleanAfterAbort();

    virtual bool ShouldIgnoreFile(const QString &filename);

    virtual QString Output() const;
};

#endif // DESHAKER_PASS2_H
