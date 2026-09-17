#ifndef TASK_H
#define TASK_H

#include <string>

enum class TaskPriority {
    Low,
    Medium,
    High
};

class Task {
public:
    Task(const std::string& title, bool completed = false, TaskPriority priority = TaskPriority::Medium);

    void markComplete();
    void updateTitle(const std::string& newTitle);
    void updatePriority(TaskPriority newPriority);
    std::string serialize() const;
    static Task deserialize(const std::string& line);

    std::string getTitle() const;
    bool isCompleted() const;
    TaskPriority getPriority() const;

private:
    std::string title;
    bool completed;
    TaskPriority priority;
};

#endif
