#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Task.h"
#include <vector>
#include <string>

/**
 * @brief Manages a collection of tasks and handles persistence.
 */
class TaskManager {
public:
    explicit TaskManager(const std::string& storageFile);

    void load();
    void save() const;

    void addTask(const std::string& title);
    void completeTask(size_t index);
    void listTasks() const;
    
    // For testing/lib usage
    const std::vector<Task>& getTasks() const;

private:
    std::vector<Task> tasks;
    std::string storageFile;
};

#endif
