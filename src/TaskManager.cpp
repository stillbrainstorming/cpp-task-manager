#include "TaskManager.h"

void TaskManager::addTask(const std::string& title) {
    tasks.emplace_back(title);
}

void TaskManager::completeTask(size_t index) {
    if (index < tasks.size()) {
        tasks[index].markComplete();
    }
}

void TaskManager::replaceTasks(std::vector<Task> newTasks) {
    tasks = newTasks;
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks;
}
