#ifndef TASKS_LIST_H
#define TASKS_LIST_H

#include <memory>
#include <QList>
#include "tasks/tasks_base.h"

class TasksList : private QList<std::shared_ptr<TasksBase>>
{
public:
    TasksList();

    std::shared_ptr<TasksBase> getSharedPtr(const TasksBase *ptr) const;

    //!
    //! \brief Append tasks to List
    //! \param newTask
    //! \return True if appended, false if not due to tasks already existing
    //!
    bool Append(std::shared_ptr<TasksBase> newTask);

    //!
    //! \brief Remove a task from the list
    //!
    void Remove(TasksBase *);

    bool ShouldIgnore(const QString &filename);

    void Clear();

    std::shared_ptr<TasksBase> Pop();

    int Size() const;
};

#endif // TASKS_LIST_H
