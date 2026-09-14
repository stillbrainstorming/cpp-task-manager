#include "TaskManager.h"
#include <stdexcept>

void TaskManager::addTask(const std::string& title) {
    tasks.emplace_back(title);
}

void TaskManager::completeTask(size_t index) {
    if (index >= tasks.size()) {
        throw std::out_of_range("Task index is out of range");
    }
    tasks[index].markComplete();
}

void TaskManager::updateTask(size_t index, const std::string& title) {
    if (index >= tasks.size()) {
        throw std::out_of_range("Task index is out of range");
    }
    tasks[index].updateTitle(title);
}

void TaskManager::deleteTask(size_t index) {
    if (index >= tasks.size()) {
        throw std::out_of_range("Task index is out of range");
    }
    tasks.erase(tasks.begin() + static_cast<std::ptrdiff_t>(index));
}

void TaskManager::replaceTasks(std::vector<Task> newTasks) {
    tasks = newTasks;
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks;
}
