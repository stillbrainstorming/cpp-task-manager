#ifndef TASK_H
#define TASK_H

#include <string>

/**
 * @brief Represents a single task in the system.
 */
class Task {
public:
    Task(const std::string& title, bool completed = false);

    void markComplete();
    std::string serialize() const;
    static Task deserialize(const std::string& line);

    std::string getTitle() const;
    bool isCompleted() const;

private:
    std::string title;
    bool completed;
};

#endif
