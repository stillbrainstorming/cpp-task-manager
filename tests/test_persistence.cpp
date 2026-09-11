#include "FileTaskRepository.h"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
const char* testFile = "task_repository_test.txt";

void writeFile(const std::string& content) {
    std::ofstream file(testFile, std::ios::trunc);
    assert(file.is_open());
    file << content;
}

void cleanup() {
    std::remove(testFile);
}
}

void testMissingFileRejected() {
    cleanup();
    FileTaskRepository repository(testFile);
    bool rejected = false;
    try {
        repository.load();
    } catch (const std::runtime_error&) {
        rejected = true;
    }
    assert(rejected);
    std::cout << "testMissingFileRejected passed!\n";
}

void testEmptyFileLoadsNoTasks() {
    writeFile("");
    FileTaskRepository repository(testFile);
    auto tasks = repository.load();
    assert(tasks.empty());
    cleanup();
    std::cout << "testEmptyFileLoadsNoTasks passed!\n";
}

void testMalformedFileRejected() {
    writeFile("not-a-task-record\n");
    FileTaskRepository repository(testFile);
    bool rejected = false;
    try {
        repository.load();
    } catch (const std::runtime_error&) {
        rejected = true;
    }
    assert(rejected);
    cleanup();
    std::cout << "testMalformedFileRejected passed!\n";
}

void testValidTasksLoadAndSave() {
    writeFile("0|First Task\n1|Finished Task\n");
    FileTaskRepository repository(testFile);
    auto tasks = repository.load();
    assert(tasks.size() == 2);
    assert(tasks[0].getTitle() == "First Task");
    assert(!tasks[0].isCompleted());
    assert(tasks[1].getTitle() == "Finished Task");
    assert(tasks[1].isCompleted());

    repository.save(tasks);
    auto reloaded = repository.load();
    assert(reloaded.size() == 2);
    assert(reloaded[0].getTitle() == "First Task");
    assert(reloaded[1].isCompleted());
    cleanup();
    std::cout << "testValidTasksLoadAndSave passed!\n";
}

int main() {
    testMissingFileRejected();
    testEmptyFileLoadsNoTasks();
    testMalformedFileRejected();
    testValidTasksLoadAndSave();
    std::cout << "All persistence tests passed successfully!\n";
    return 0;
}
