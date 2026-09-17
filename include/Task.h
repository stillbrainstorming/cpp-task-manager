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
    Task(const std::string& title, bool completed = false, TaskPriority priority = TaskPriority::Medium, const std::string& dueDate = "");

    void markComplete();
    void updateTitle(const std::string& newTitle);
    void updatePriority(TaskPriority newPriority);
    void updateDueDate(const std::string& newDueDate);
    std::string serialize() const;
    static Task deserialize(const std::string& line);

    std::string getTitle() const;
    bool isCompleted() const;
    TaskPriority getPriority() const;
    std::string getDueDate() const;

private:
    std::string title;
    bool completed;
    TaskPriority priority;
    std::string dueDate;
};

#endif
