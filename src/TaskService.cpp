#include "TaskService.h"

TaskService::TaskService(TaskManager& manager, TaskRepository& repository)
    : manager(manager), repository(repository) {}

void TaskService::load() {
    manager.replaceTasks(repository.load());
}

void TaskService::save() {
    repository.save(manager.getTasks());
}

void TaskService::addTask(const std::string& title) {
    manager.addTask(title);
}

void TaskService::completeTask(size_t index) {
    manager.completeTask(index);
}

const std::vector<Task>& TaskService::getTasks() const {
    return manager.getTasks();
}
