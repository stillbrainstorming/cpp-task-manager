#include "FileTaskRepository.h"
#include <fstream>

FileTaskRepository::FileTaskRepository(const std::string& storageFile)
    : storageFile(storageFile) {}

std::vector<Task> FileTaskRepository::load() {
    std::vector<Task> tasks;
    std::ifstream file(storageFile);
    if (!file.is_open()) return tasks;

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            tasks.push_back(Task::deserialize(line));
        }
    }
    return tasks;
}

void FileTaskRepository::save(const std::vector<Task>& tasks) {
    std::ofstream file(storageFile);
    for (const auto& task : tasks) {
        file << task.serialize() << "\n";
    }
}
