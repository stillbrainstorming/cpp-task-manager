#include "FileTaskRepository.h"
#include "TaskManager.h"
#include "TaskService.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <stdexcept>

namespace { const char* testFile = "task_service_test.txt"; }

void cleanup() { std::remove(testFile); }

void testLifecycleThroughService() {
    cleanup();
    TaskManager manager;
    FileTaskRepository repository(testFile);
    TaskService service(manager, repository);
    service.addTask("Service Task", TaskPriority::High, "2026-10-01");
    assert(service.getTasks().size() == 1);
    assert(service.getTasks()[0].getPriority() == TaskPriority::High);
    assert(service.getTasks()[0].getDueDate() == "2026-10-01");
    service.completeTask(0);
    assert(service.getTasks()[0].isCompleted());
    service.updateTask(0, "Updated Service Task", TaskPriority::Low, "2026-10-15");
    assert(service.getTasks()[0].getTitle() == "Updated Service Task");
    assert(service.getTasks()[0].getPriority() == TaskPriority::Low);
    assert(service.getTasks()[0].getDueDate() == "2026-10-15");
    service.deleteTask(0);
    assert(service.getTasks().empty());
    cleanup();
}

void testFilteringThroughService() {
    TaskManager manager;
    FileTaskRepository repository(testFile);
    TaskService service(manager, repository);
    service.addTask("High", TaskPriority::High, "2026-09-01");
    service.addTask("Medium", TaskPriority::Medium, "2026-09-20");
    service.addTask("Future", TaskPriority::High, "2026-10-01");
    const auto high = service.filterByPriority(TaskPriority::High);
    assert(high.size() == 2);
    const auto overdue = service.filterOverdue("2026-09-20");
    assert(overdue.size() == 1);
    assert(overdue[0].getTitle() == "High");
    cleanup();
}

void testPersistenceThroughService() {
    cleanup();
    {
        TaskManager manager;
        FileTaskRepository repository(testFile);
        TaskService service(manager, repository);
        service.addTask("Persisted", TaskPriority::High, "2026-12-31");
        service.save();
    }
    {
        TaskManager manager;
        FileTaskRepository repository(testFile);
        TaskService service(manager, repository);
        service.load();
        assert(service.getTasks().size() == 1);
        assert(service.getTasks()[0].getTitle() == "Persisted");
        assert(service.getTasks()[0].getPriority() == TaskPriority::High);
        assert(service.getTasks()[0].getDueDate() == "2026-12-31");
    }
    cleanup();
}

void testInvalidLifecycleOperationsDoNotMutateState() {
    TaskManager manager;
    FileTaskRepository repository(testFile);
    TaskService service(manager, repository);
    service.addTask("Stable", TaskPriority::Medium, "2026-11-01");
    bool rejected = false;
    try { service.completeTask(1); } catch (const std::out_of_range&) { rejected = true; }
    assert(rejected && service.getTasks().size() == 1);
    assert(!service.getTasks()[0].isCompleted());
    rejected = false;
    try { service.updateTask(1, "Changed", TaskPriority::High, "2026-12-01"); } catch (const std::out_of_range&) { rejected = true; }
    assert(rejected);
    assert(service.getTasks()[0].getTitle() == "Stable");
    assert(service.getTasks()[0].getPriority() == TaskPriority::Medium);
    assert(service.getTasks()[0].getDueDate() == "2026-11-01");
    rejected = false;
    try { service.deleteTask(1); } catch (const std::out_of_range&) { rejected = true; }
    assert(rejected && service.getTasks().size() == 1);
    cleanup();
}

int main() {
    testLifecycleThroughService();
    testFilteringThroughService();
    testPersistenceThroughService();
    testInvalidLifecycleOperationsDoNotMutateState();
    std::cout << "All service tests passed successfully!\n";
    return 0;
}
