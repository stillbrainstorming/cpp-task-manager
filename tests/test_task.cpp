#include "Task.h"
#include "TaskManager.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

void testTaskCreation() {
    Task t("Test Task");
    assert(t.getTitle() == "Test Task");
    assert(!t.isCompleted());
    assert(t.getPriority() == TaskPriority::Medium);
    std::cout << "testTaskCreation passed!\n";
}

void testTaskCompletion() {
    Task t("Complete Me");
    t.markComplete();
    assert(t.isCompleted());
    std::cout << "testTaskCompletion passed!\n";
}

void testSerialization() {
    Task t("Serialize", true, TaskPriority::High);
    std::string s = t.serialize();
    assert(s == "1|H|Serialize");

    Task t2 = Task::deserialize(s);
    assert(t2.getTitle() == "Serialize");
    assert(t2.isCompleted());
    assert(t2.getPriority() == TaskPriority::High);
    std::cout << "testSerialization passed!\n";
}

void testLegacySerialization() {
    Task t = Task::deserialize("0|Legacy Task");
    assert(t.getTitle() == "Legacy Task");
    assert(!t.isCompleted());
    assert(t.getPriority() == TaskPriority::Medium);
    std::cout << "testLegacySerialization passed!\n";
}

void testEmptyTitleRejected() {
    bool rejected = false;
    try {
        Task t("   ");
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
    std::cout << "testEmptyTitleRejected passed!\n";
}

void testInvalidCompletionIndexRejected() {
    TaskManager manager;
    manager.addTask("Valid Task");

    bool rejected = false;
    try {
        manager.completeTask(1);
    } catch (const std::out_of_range&) {
        rejected = true;
    }
    assert(rejected);
    assert(!manager.getTasks().at(0).isCompleted());
    std::cout << "testInvalidCompletionIndexRejected passed!\n";
}

void testPriorityFiltering() {
    TaskManager manager;
    manager.addTask("Low Task", TaskPriority::Low);
    manager.addTask("High Task", TaskPriority::High);
    manager.addTask("Another High Task", TaskPriority::High);

    const auto filtered = manager.filterByPriority(TaskPriority::High);
    assert(filtered.size() == 2);
    assert(filtered[0].getTitle() == "High Task");
    assert(filtered[1].getTitle() == "Another High Task");
    std::cout << "testPriorityFiltering passed!\n";
}

void testPriorityUpdate() {
    TaskManager manager;
    manager.addTask("Task", TaskPriority::Low);
    manager.updateTask(0, "Updated", TaskPriority::High);
    assert(manager.getTasks().at(0).getPriority() == TaskPriority::High);
    assert(manager.getTasks().at(0).getTitle() == "Updated");
    std::cout << "testPriorityUpdate passed!\n";
}

int main() {
    testTaskCreation();
    testTaskCompletion();
    testSerialization();
    testLegacySerialization();
    testEmptyTitleRejected();
    testInvalidCompletionIndexRejected();
    testPriorityFiltering();
    testPriorityUpdate();
    std::cout << "All tests passed successfully!\n";
    return 0;
}
