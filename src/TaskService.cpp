#include "TaskService.h"

TaskService::TaskService(TaskManager& manager, TaskRepository& repository)
    : manager(manager), repository(repository) {}

void TaskService::load() {
    manager.replaceTasks(repository.load());
}

void TaskService::save() {
    repository.save(manager.getTasks());
}

void TaskService::addTask(const std::string& title, TaskPriority priority) {
    manager.addTask(title, priority);
}

void TaskService::completeTask(size_t index) {
    manager.completeTask(index);
}

void TaskService::updateTask(size_t index, const std::string& title, TaskPriority priority) {
    manager.updateTask(index, title, priority);
}

void TaskService::deleteTask(size_t index) {
    manager.deleteTask(index);
}

std::vector<Task> TaskService::filterByPriority(TaskPriority priority) const {
    return manager.filterByPriority(priority);
}

const std::vector<Task>& TaskService::getTasks() const {
    return manager.getTasks();
}
