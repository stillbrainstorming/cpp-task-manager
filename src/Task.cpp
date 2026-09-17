#include "Task.h"
#include <cctype>
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

bool validDate(const std::string& value) {
    if (value.empty()) return true;
    if (value.size() != 10 || value[4] != '-' || value[7] != '-') return false;
    for (size_t i = 0; i < value.size(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(static_cast<unsigned char>(value[i]))) return false;
    }

    int year = std::stoi(value.substr(0, 4));
    int month = std::stoi(value.substr(5, 2));
    int day = std::stoi(value.substr(8, 2));
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;

    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];
    if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) maxDay = 29;
    return day <= maxDay;
}
}

Task::Task(const std::string& title, bool completed, TaskPriority priority, const std::string& dueDate)
    : title(title), completed(completed), priority(priority), dueDate(dueDate) {
    if (title.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
        throw std::invalid_argument("Task title cannot be empty");
    }
    if (!validDate(dueDate)) {
        throw std::invalid_argument("Due date must use YYYY-MM-DD");
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

void Task::updateDueDate(const std::string& newDueDate) {
    if (!validDate(newDueDate)) {
        throw std::invalid_argument("Due date must use YYYY-MM-DD");
    }
    dueDate = newDueDate;
}

std::string Task::serialize() const {
    return (completed ? "1" : "0") + std::string("|") + priorityCode(priority) + "|" + dueDate + "|" + title;
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

    size_t thirdSep = line.find('|', secondSep + 1);
    if (thirdSep == std::string::npos) {
        return Task(line.substr(secondSep + 1), completed, parsePriority(line[firstSep + 1]));
    }

    return Task(line.substr(thirdSep + 1), completed, parsePriority(line[firstSep + 1]), line.substr(secondSep + 1, thirdSep - secondSep - 1));
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

std::string Task::getDueDate() const {
    return dueDate;
}
