#include "FileTaskRepository.h"
#include "TaskService.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

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

TaskPriority parsePriority(const std::string& value) {
    if (value == "low") return TaskPriority::Low;
    if (value == "medium") return TaskPriority::Medium;
    if (value == "high") return TaskPriority::High;
    throw std::invalid_argument("Priority must be low, medium, or high");
}

std::string parseDueDate(const std::string& value) {
    if (value == "none") return "";
    Task validationTask("date validation", false, TaskPriority::Medium, value);
    return validationTask.getDueDate();
}

std::string priorityLabel(TaskPriority priority) {
    switch (priority) {
    case TaskPriority::Low: return "low";
    case TaskPriority::Medium: return "medium";
    case TaskPriority::High: return "high";
    }
    throw std::invalid_argument("Invalid task priority");
}

void listTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i << ". "
                  << (tasks[i].isCompleted() ? "[x] " : "[ ] ")
                  << "[" << priorityLabel(tasks[i].getPriority()) << "] "
                  << tasks[i].getTitle();
        if (!tasks[i].getDueDate().empty()) {
            std::cout << " (due " << tasks[i].getDueDate() << ")";
        }
        std::cout << "\n";
    }
}

size_t parseTaskIndex(const std::string& value) {
    size_t parsedCharacters = 0;
    unsigned long index = 0;

    try {
        index = std::stoul(value, &parsedCharacters);
    } catch (const std::exception&) {
        throw std::invalid_argument("Task index must be a non-negative integer");
    }

    if (parsedCharacters != value.size()) {
        throw std::invalid_argument("Task index must be a non-negative integer");
    }

    return static_cast<size_t>(index);
}

int main(int argc, char* argv[]) {
    Config config = loadConfig("config.json");

    std::cout << "--- " << config.app_name << " ---" << std::endl;

    TaskManager manager;
    FileTaskRepository repository(config.storage_path);
    TaskService service(manager, repository);

    try {
        service.load();

        if (argc < 2) {
            std::cout << "Usage:\n"
                      << "  add <task> [low|medium|high] [YYYY-MM-DD|none]\n"
                      << "  update <index> <task> [low|medium|high] [YYYY-MM-DD|none]\n"
                      << "  complete <index>\n"
                      << "  delete <index>\n"
                      << "  list [low|medium|high]\n"
                      << "  overdue <YYYY-MM-DD>\n";
            return 1;
        }

        std::string command = argv[1];

        if (command == "add") {
            if (argc < 3 || std::string(argv[2]).empty()) {
                throw std::invalid_argument("The add command requires a task title");
            }
            TaskPriority priority = argc >= 4 ? parsePriority(argv[3]) : TaskPriority::Medium;
            std::string dueDate = argc >= 5 ? parseDueDate(argv[4]) : "";
            service.addTask(argv[2], priority, dueDate);
            service.save();
            std::cout << "Task added successfully.\n";
        } else if (command == "update") {
            if (argc < 4 || std::string(argv[3]).empty()) {
                throw std::invalid_argument("The update command requires an index and task title");
            }
            size_t index = parseTaskIndex(argv[2]);
            TaskPriority priority = argc >= 5 ? parsePriority(argv[4]) : service.getTasks().at(index).getPriority();
            std::string dueDate = argc >= 6 ? parseDueDate(argv[5]) : service.getTasks().at(index).getDueDate();
            service.updateTask(index, argv[3], priority, dueDate);
            service.save();
            std::cout << "Task updated successfully.\n";
        } else if (command == "complete") {
            if (argc < 3) {
                throw std::invalid_argument("The complete command requires a task index");
            }
            service.completeTask(parseTaskIndex(argv[2]));
            service.save();
            std::cout << "Task marked as complete.\n";
        } else if (command == "delete") {
            if (argc < 3) {
                throw std::invalid_argument("The delete command requires a task index");
            }
            service.deleteTask(parseTaskIndex(argv[2]));
            service.save();
            std::cout << "Task deleted successfully.\n";
        } else if (command == "list") {
            if (argc >= 3) {
                listTasks(service.filterByPriority(parsePriority(argv[2])));
            } else {
                listTasks(service.getTasks());
            }
        } else if (command == "overdue") {
            if (argc < 3) {
                throw std::invalid_argument("The overdue command requires a reference date");
            }
            std::string referenceDate = parseDueDate(argv[2]);
            if (referenceDate.empty()) {
                throw std::invalid_argument("The overdue command requires a valid reference date");
            }
            listTasks(service.filterOverdue(referenceDate));
        } else {
            throw std::invalid_argument("Unknown command: " + command);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
