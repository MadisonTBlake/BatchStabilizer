#ifndef MPEG_CONVERSION_H
#define MPEG_CONVERSION_H

#include <QString>

#include "tasks_base.h"

class MPEGConversion : public TasksBase
{
    QString m_Filename;
    QString m_FFMPEGPath;
public:
    MPEGConversion(const QString &ffmpegPath, const QString &filename);

    ~MPEGConversion();

    QString Filename() const;

    QString FFMPEGPath() const;

    virtual TasksTypes Type() const;

    virtual void Execute();

    virtual bool Equal(const TasksBase &that);

    virtual void CleanAfterAbort();

    virtual bool ShouldIgnoreFile(const QString &filename);

    virtual QString Output() const;
};

#endif // MPEG_CONVERSION_H
