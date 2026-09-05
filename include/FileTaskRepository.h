#ifndef FILE_TASK_REPOSITORY_H
#define FILE_TASK_REPOSITORY_H

#include "TaskRepository.h"
#include <string>

class FileTaskRepository : public TaskRepository {
public:
    explicit FileTaskRepository(const std::string& storageFile);

    std::vector<Task> load() override;
    void save(const std::vector<Task>& tasks) override;

private:
    std::string storageFile;
};

#endif
