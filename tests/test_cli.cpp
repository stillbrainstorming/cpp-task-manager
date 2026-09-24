#define main task_manager_program_main
#include "../src/main.cpp"
#undef main

#include <cassert>
#include <cstdio>
#include <fstream>
#include <string>

void expectInvalidTaskIndex(const std::string& value)
{
    bool failed = false;
    try
    {
        parseTaskIndex(value);
    }
    catch (const std::invalid_argument&)
    {
        failed = true;
    }
    assert(failed);
}

void expectInvalidPriority(const std::string& value)
{
    bool failed = false;
    try
    {
        parsePriority(value);
    }
    catch (const std::invalid_argument&)
    {
        failed = true;
    }
    assert(failed);
}

void expectInvalidDueDate(const std::string& value)
{
    bool failed = false;
    try
    {
        parseDueDate(value);
    }
    catch (const std::exception&)
    {
        failed = true;
    }
    assert(failed);
}

void testTaskIndexParsing()
{
    assert(parseTaskIndex("0") == 0);
    assert(parseTaskIndex("42") == 42);
    expectInvalidTaskIndex("");
    expectInvalidTaskIndex("-1");
    expectInvalidTaskIndex("1x");
}

void testPriorityParsing()
{
    assert(parsePriority("low") == TaskPriority::Low);
    assert(parsePriority("medium") == TaskPriority::Medium);
    assert(parsePriority("high") == TaskPriority::High);
    expectInvalidPriority("");
    expectInvalidPriority("urgent");
    expectInvalidPriority("HIGH");
}

void testDueDateParsing()
{
    assert(parseDueDate("2026-10-01") == "2026-10-01");
    assert(parseDueDate("none").empty());
    expectInvalidDueDate("");
    expectInvalidDueDate("2026-02-30");
    expectInvalidDueDate("01-10-2026");
}

void testConfigFallback()
{
    const std::string path = "test-config-fallback.json";
    std::remove(path.c_str());

    Config config = loadConfig(path);
    assert(config.storage_path == "data/tasks.txt");
    assert(config.app_name == "Task Manager");
}

void testConfiguredValues()
{
    const std::string path = "test-config-values.json";
    {
        std::ofstream file(path);
        file << R"({"storage_path":"data/custom.txt","app_name":"Custom Manager"})";
    }

    Config config = loadConfig(path);
    assert(config.storage_path == "data/custom.txt");
    assert(config.app_name == "Custom Manager");
    std::remove(path.c_str());
}

int main()
{
    testTaskIndexParsing();
    testPriorityParsing();
    testDueDateParsing();
    testConfigFallback();
    testConfiguredValues();
    return 0;
}
