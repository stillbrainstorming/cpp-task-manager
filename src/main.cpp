#include "FileTaskRepository.h"
#include "TaskService.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Config {
    std::string storage_path;
    std::string app_name;
};

Config loadConfig(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return {"data/tasks.txt", "Task Manager"};
    }
    json j;
    file >> j;
    return {
        j.value("storage_path", "data/tasks.txt"),
        j.value("app_name", "Task Manager")
    };
}

void listTasks(const TaskService& service) {
    const auto& tasks = service.getTasks();
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

int main(int argc, char* argv[]) {
    Config config = loadConfig("config.json");

    std::cout << "--- " << config.app_name << " ---" << std::endl;

    TaskManager manager;
    FileTaskRepository repository(config.storage_path);
    TaskService service(manager, repository);
    service.load();

    if (argc < 2) {
        std::cout << "Usage:\n"
                  << "  add <task>\n"
                  << "  complete <index>\n"
                  << "  list\n";
        return 0;
    }

    std::string command = argv[1];

    try {
        if (command == "add" && argc >= 3) {
            service.addTask(argv[2]);
            service.save();
            std::cout << "Task added successfully.\n";
        } else if (command == "complete" && argc >= 3) {
            service.completeTask(std::stoul(argv[2]));
            service.save();
            std::cout << "Task marked as complete.\n";
        } else if (command == "list") {
            listTasks(service);
        } else {
            std::cout << "Invalid command\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
