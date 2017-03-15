#ifndef DESHAKER_GENERIC_H
#define DESHAKER_GENERIC_H

#include <QString>

#include "tasks_base.h"

class DeshakerGeneric : public TasksBase
{
protected:

    QString m_VDubPath;
    QString m_Filename;

public:
    DeshakerGeneric(const QString &VDubPath, const QString &filename);

    QString Filename() const {
        return m_Filename;
    }
};

#endif // DESHAKER_GENERIC_H
