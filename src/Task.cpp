#include "Task.h"
#include <sstream>
#include <stdexcept>

Task::Task(const std::string& title, bool completed)
    : title(title), completed(completed) {
    if (title.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
        throw std::invalid_argument("Task title cannot be empty");
    }
}

void Task::markComplete() {
    completed = true;
}

std::string Task::serialize() const {
    return (completed ? "1" : "0") + std::string("|") + title;
}

Task Task::deserialize(const std::string& line) {
    size_t sep = line.find('|');
    if (sep == std::string::npos || sep != 1 || (line[0] != '0' && line[0] != '1')) {
        throw std::invalid_argument("Malformed task record");
    }

    bool completed = line[0] == '1';
    std::string title = line.substr(sep + 1);
    return Task(title, completed);
}

std::string Task::getTitle() const {
    return title;
}

bool Task::isCompleted() const {
    return completed;
}
