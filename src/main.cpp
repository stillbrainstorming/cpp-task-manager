#include "TaskManager.h"
#include <iostream>
#include <fstream>
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

int main(int argc, char* argv[]) {
    Config config = loadConfig("config.json");
    
    std::cout << "--- " << config.app_name << " ---" << std::endl;

    TaskManager manager(config.storage_path);
    manager.load();

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
            manager.addTask(argv[2]);
            manager.save();
            std::cout << "Task added successfully.\n";
        } else if (command == "complete" && argc >= 3) {
            manager.completeTask(std::stoul(argv[2]));
            manager.save();
            std::cout << "Task marked as complete.\n";
        } else if (command == "list") {
            manager.listTasks();
        } else {
            std::cout << "Invalid command\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
