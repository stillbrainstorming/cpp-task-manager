#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Task.h"
#include <string>
#include <vector>

class TaskManager {
public:
    TaskManager() = default;

    void addTask(const std::string& title, TaskPriority priority = TaskPriority::Medium, const std::string& dueDate = "");
    void completeTask(size_t index);
    void updateTask(size_t index, const std::string& title, TaskPriority priority = TaskPriority::Medium, const std::string& dueDate = "");
    void deleteTask(size_t index);
    void replaceTasks(std::vector<Task> newTasks);
    std::vector<Task> filterByPriority(TaskPriority priority) const;
    std::vector<Task> filterOverdue(const std::string& referenceDate) const;
    const std::vector<Task>& getTasks() const;

private:
    std::vector<Task> tasks;
};

#endif
