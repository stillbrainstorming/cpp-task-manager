#include "Task.h"
#include "TaskManager.h"
#include <cassert>
#include <iostream>

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

int main() {
    testTaskCreation();
    testTaskCompletion();
    testSerialization();
    std::cout << "All tests passed successfully!\n";
    return 0;
}
