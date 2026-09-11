#include "FileTaskRepository.h"
#include <fstream>
#include <stdexcept>

FileTaskRepository::FileTaskRepository(const std::string& storageFile)
    : storageFile(storageFile) {}

std::vector<Task> FileTaskRepository::load() {
    std::ifstream file(storageFile);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open task storage file: " + storageFile);
    }

    std::vector<Task> tasks;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        try {
            tasks.push_back(Task::deserialize(line));
        } catch (const std::exception& error) {
            throw std::runtime_error("Invalid task data in storage file: " + std::string(error.what()));
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Failed while reading task storage file: " + storageFile);
    }

    return tasks;
}

void FileTaskRepository::save(const std::vector<Task>& tasks) {
    std::ofstream file(storageFile, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open task storage file for writing: " + storageFile);
    }

    for (const auto& task : tasks) {
        file << task.serialize() << "\n";
        if (!file) {
            throw std::runtime_error("Failed while writing task storage file: " + storageFile);
        }
    }
}
