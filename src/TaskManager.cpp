#include "TaskManager.h"
#include <fstream>
#include <iostream>

TaskManager::TaskManager(const std::string& storageFile)
    : storageFile(storageFile) {}

void TaskManager::load() {
    tasks.clear();
    std::ifstream file(storageFile);
    if (!file.is_open()) return;
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            tasks.push_back(Task::deserialize(line));
        }
    }
}

void TaskManager::save() const {
    std::ofstream file(storageFile);
    for (const auto& task : tasks) {
        file << task.serialize() << "\n";
    }
}

void TaskManager::addTask(const std::string& title) {
    tasks.emplace_back(title);
}

void TaskManager::completeTask(size_t index) {
    if (index < tasks.size()) {
        tasks[index].markComplete();
    }
}

void TaskManager::listTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i << ". "
                  << (tasks[i].isCompleted() ? "[x] " : "[ ] ")
                  << tasks[i].getTitle() << "\n";
    }
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks;
}
