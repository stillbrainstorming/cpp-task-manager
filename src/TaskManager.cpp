#include "TaskManager.h"
#include <stdexcept>

void TaskManager::addTask(const std::string& title, TaskPriority priority, const std::string& dueDate) {
    tasks.emplace_back(title, false, priority, dueDate);
}

void TaskManager::completeTask(size_t index) {
    if (index >= tasks.size()) {
        throw std::out_of_range("Task index is out of range");
    }
    tasks[index].markComplete();
}

void TaskManager::updateTask(size_t index, const std::string& title, TaskPriority priority, const std::string& dueDate) {
    if (index >= tasks.size()) {
        throw std::out_of_range("Task index is out of range");
    }
    tasks[index].updateTitle(title);
    tasks[index].updatePriority(priority);
    tasks[index].updateDueDate(dueDate);
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

std::vector<Task> TaskManager::filterByPriority(TaskPriority priority) const {
    std::vector<Task> filtered;
    for (const auto& task : tasks) {
        if (task.getPriority() == priority) {
            filtered.push_back(task);
        }
    }
    return filtered;
}

std::vector<Task> TaskManager::filterOverdue(const std::string& referenceDate) const {
    std::vector<Task> filtered;
    for (const auto& task : tasks) {
        if (!task.isCompleted() && !task.getDueDate().empty() && task.getDueDate() < referenceDate) {
            filtered.push_back(task);
        }
    }
    return filtered;
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks;
}
