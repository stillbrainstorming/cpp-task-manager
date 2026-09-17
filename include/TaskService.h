#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include "TaskManager.h"
#include "TaskRepository.h"

class TaskService {
public:
    TaskService(TaskManager& manager, TaskRepository& repository);

    void load();
    void save();
    void addTask(const std::string& title, TaskPriority priority = TaskPriority::Medium, const std::string& dueDate = "");
    void completeTask(size_t index);
    void updateTask(size_t index, const std::string& title, TaskPriority priority = TaskPriority::Medium, const std::string& dueDate = "");
    void deleteTask(size_t index);
    std::vector<Task> filterByPriority(TaskPriority priority) const;
    std::vector<Task> filterOverdue(const std::string& referenceDate) const;
    const std::vector<Task>& getTasks() const;

private:
    TaskManager& manager;
    TaskRepository& repository;
};

#endif
