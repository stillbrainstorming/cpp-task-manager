#ifndef TASK_REPOSITORY_H
#define TASK_REPOSITORY_H

#include "Task.h"
#include <vector>

class TaskRepository {
public:
    virtual ~TaskRepository() = default;
    virtual std::vector<Task> load() = 0;
    virtual void save(const std::vector<Task>& tasks) = 0;
};

#endif
