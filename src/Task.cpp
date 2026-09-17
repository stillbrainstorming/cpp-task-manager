#include "Task.h"
#include <stdexcept>

namespace {
char priorityCode(TaskPriority priority) {
    switch (priority) {
    case TaskPriority::Low: return 'L';
    case TaskPriority::Medium: return 'M';
    case TaskPriority::High: return 'H';
    }
    throw std::invalid_argument("Invalid task priority");
}

TaskPriority parsePriority(char value) {
    switch (value) {
    case 'L': return TaskPriority::Low;
    case 'M': return TaskPriority::Medium;
    case 'H': return TaskPriority::High;
    default: throw std::invalid_argument("Invalid task priority");
    }
}
}

Task::Task(const std::string& title, bool completed, TaskPriority priority)
    : title(title), completed(completed), priority(priority) {
    if (title.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
        throw std::invalid_argument("Task title cannot be empty");
    }
}

void Task::markComplete() {
    completed = true;
}

void Task::updateTitle(const std::string& newTitle) {
    if (newTitle.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
        throw std::invalid_argument("Task title cannot be empty");
    }
    title = newTitle;
}

void Task::updatePriority(TaskPriority newPriority) {
    priority = newPriority;
}

std::string Task::serialize() const {
    return (completed ? "1" : "0") + std::string("|") + priorityCode(priority) + "|" + title;
}

Task Task::deserialize(const std::string& line) {
    size_t firstSep = line.find('|');
    if (firstSep != 1 || (line[0] != '0' && line[0] != '1')) {
        throw std::invalid_argument("Malformed task record");
    }

    bool completed = line[0] == '1';
    size_t secondSep = line.find('|', firstSep + 1);
    if (secondSep == std::string::npos) {
        return Task(line.substr(firstSep + 1), completed, TaskPriority::Medium);
    }

    if (secondSep != firstSep + 2) {
        throw std::invalid_argument("Malformed task record");
    }

    return Task(line.substr(secondSep + 1), completed, parsePriority(line[firstSep + 1]));
}

std::string Task::getTitle() const {
    return title;
}

bool Task::isCompleted() const {
    return completed;
}

TaskPriority Task::getPriority() const {
    return priority;
}
