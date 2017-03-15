#include "tasks_list.h"

TasksList::TasksList()
{

}


//!
//! \brief Append tasks to List
//! \param newTask
//! \return True if appended, false if not due to tasks already existing
//!
bool TasksList::Append(std::shared_ptr<TasksBase> newTask)
{
    bool copy = false;
    for(auto it = this->cbegin() ; it != this->cend() ; ++it) {
        if((*it)->Equal(*newTask)) {
            copy = true;
            break;
        }
    }

    if(copy == false) {
        this->push_back(newTask);
        return true;
    }
    return false;
}

bool TasksList::ShouldIgnore(const QString &filename)
{
    for(auto it = this->cbegin() ; it != this->cend() ; ++it) {
        if((*it)->ShouldIgnoreFile(filename) == true) {
            return true;
        }
    }

    return false;
}


//!
//! \brief Remove a task from the list
//!
void TasksList::Remove(TasksBase * ptr) {
    int i = 0;
    for(auto it = this->cbegin() ; it != this->cend() ; ++it) {
        if((*it).get() == ptr) {
            removeAt(i);
            break;
        }
        i++;
    }
}


void TasksList::Clear()
{
    this->clear();
}

std::shared_ptr<TasksBase> TasksList::Pop()
{
    auto value = this->at(0);
    removeFirst();
    return value;
}


int TasksList::Size() const  {
    return this->size();
}
