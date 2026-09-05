#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Task.h"
#include <string>
#include <vector>

class TaskManager {
public:
    TaskManager() = default;

    void addTask(const std::string& title);
    void completeTask(size_t index);
    void replaceTasks(std::vector<Task> newTasks);
    const std::vector<Task>& getTasks() const;

private:
    std::vector<Task> tasks;
};

#endif
