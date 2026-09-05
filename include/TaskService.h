#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include "TaskManager.h"
#include "TaskRepository.h"

class TaskService {
public:
    TaskService(TaskManager& manager, TaskRepository& repository);

    void load();
    void save();
    void addTask(const std::string& title);
    void completeTask(size_t index);
    const std::vector<Task>& getTasks() const;

private:
    TaskManager& manager;
    TaskRepository& repository;
};

#endif
