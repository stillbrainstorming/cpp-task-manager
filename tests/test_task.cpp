#include "Task.h"
#include "TaskManager.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

void testTaskCreation() {
    Task t("Test Task");
    assert(t.getTitle() == "Test Task");
    assert(!t.isCompleted());
    std::cout << "testTaskCreation passed!\n";
}

void testTaskCompletion() {
    Task t("Complete Me");
    t.markComplete();
    assert(t.isCompleted());
    std::cout << "testTaskCompletion passed!\n";
}

void testSerialization() {
    Task t("Serialize", true);
    std::string s = t.serialize();
    assert(s == "1|Serialize");

    Task t2 = Task::deserialize(s);
    assert(t2.getTitle() == "Serialize");
    assert(t2.isCompleted() == true);
    std::cout << "testSerialization passed!\n";
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

int main() {
    testTaskCreation();
    testTaskCompletion();
    testSerialization();
    testEmptyTitleRejected();
    testInvalidCompletionIndexRejected();
    std::cout << "All tests passed successfully!\n";
    return 0;
}
