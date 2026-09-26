#define main task_manager_program_main
#include "../src/main.cpp"
#undef main

#include <cassert>
#include <cstdio>
#include <fstream>
#include <string>

void writeFile(const std::string& path, const std::string& content)
{
    std::ofstream file(path);
    file << content;
}

void removeFile(const std::string& path)
{
    std::remove(path.c_str());
}

void testMissingConfigUsesDefaults()
{
    const std::string path = "test-config-missing.json";
    removeFile(path);

    Config config = loadConfig(path);
    assert(config.storage_path == "data/tasks.txt");
    assert(config.app_name == "Task Manager");
}

void testValidConfigUsesValues()
{
    const std::string path = "test-config-valid.json";
    writeFile(path, R"({"storage_path":"data/custom.txt","app_name":"Custom Manager"})");

    Config config = loadConfig(path);
    assert(config.storage_path == "data/custom.txt");
    assert(config.app_name == "Custom Manager");
    removeFile(path);
}

void testMalformedConfigUsesDefaults()
{
    const std::string path = "test-config-malformed.json";
    writeFile(path, R"({"storage_path": "data/custom.txt",)");

    Config config = loadConfig(path);
    assert(config.storage_path == "data/tasks.txt");
    assert(config.app_name == "Task Manager");
    removeFile(path);
}

void testNonObjectConfigUsesDefaults()
{
    const std::string path = "test-config-array.json";
    writeFile(path, "[]");

    Config config = loadConfig(path);
    assert(config.storage_path == "data/tasks.txt");
    assert(config.app_name == "Task Manager");
    removeFile(path);
}

void testInvalidFieldTypesFallBackIndividually()
{
    const std::string path = "test-config-types.json";
    writeFile(path, R"({"storage_path":42,"app_name":[]})");

    Config config = loadConfig(path);
    assert(config.storage_path == "data/tasks.txt");
    assert(config.app_name == "Task Manager");
    removeFile(path);
}

void testBlankValuesUseDefaults()
{
    const std::string path = "test-config-blank.json";
    writeFile(path, R"({"storage_path":"   ","app_name":"	"})");

    Config config = loadConfig(path);
    assert(config.storage_path == "data/tasks.txt");
    assert(config.app_name == "Task Manager");
    removeFile(path);
}

int main()
{
    testMissingConfigUsesDefaults();
    testValidConfigUsesValues();
    testMalformedConfigUsesDefaults();
    testNonObjectConfigUsesDefaults();
    testInvalidFieldTypesFallBackIndividually();
    testBlankValuesUseDefaults();
    return 0;
}
