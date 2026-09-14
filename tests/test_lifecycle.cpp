#include "TaskManager.h"
#include <cassert>
#include <stdexcept>

int main() {
    TaskManager manager;
    manager.addTask("First task");
    manager.addTask("Second task");

    manager.updateTask(0, "Renamed task");
    assert(manager.getTasks().at(0).getTitle() == "Renamed task");

    manager.deleteTask(1);
    assert(manager.getTasks().size() == 1);

    bool updateFailed = false;
    try {
        manager.updateTask(4, "Invalid");
    } catch (const std::out_of_range&) {
        updateFailed = true;
    }
    assert(updateFailed);

    bool deleteFailed = false;
    try {
        manager.deleteTask(4);
    } catch (const std::out_of_range&) {
        deleteFailed = true;
    }
    assert(deleteFailed);

    bool emptyTitleRejected = false;
    try {
        manager.updateTask(0, "   ");
    } catch (const std::invalid_argument&) {
        emptyTitleRejected = true;
    }
    assert(emptyTitleRejected);
    assert(manager.getTasks().at(0).getTitle() == "Renamed task");

    return 0;
}
