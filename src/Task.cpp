#include "Task.h"
#include <sstream>

Task::Task(const std::string& title, bool completed)
    : title(title), completed(completed) {}

void Task::markComplete() {
    completed = true;
}

std::string Task::serialize() const {
    return (completed ? "1" : "0") + std::string("|") + title;
}

Task Task::deserialize(const std::string& line) {
    size_t sep = line.find('|');
    if (sep == std::string::npos) return Task(line, false);
    
    bool completed = line.substr(0, sep) == "1";
    std::string title = line.substr(sep + 1);
    return Task(title, completed);
}

std::string Task::getTitle() const {
    return title;
}

bool Task::isCompleted() const {
    return completed;
}
