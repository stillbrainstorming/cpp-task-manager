# Task Manager Pro

A professional, library-based C++ Task Manager application. This project is structured as a robust starter template for modern C++ development.

## Key Features

- **Library-based Architecture**: Core logic resides in `TaskManagerLib`.
- **JSON Configuration**: Configuration managed via `config.json`.
- **Task Metadata**: Tasks support priority and optional due dates.
- **Filtering**: Tasks can be filtered by priority or overdue status.
- **Doxygen Documentation**: Automatic API documentation generation.
- **Cross-Platform**: Full support for Windows (MSVC) and Linux (GCC/Clang).
- **Automated CI**: GitHub Actions workflows for multi-platform builds and tests.

## Build and Run

### Prerequisites

- CMake 3.14+
- A C++17 compatible compiler
- Doxygen (Optional, for documentation)

### Compilation

```bash
# Create build directory
cmake -S . -B build

# Build the project
cmake --build build
```

### Usage

```bash
# Add a task with priority and due date
./build/task_app add "Prepare release" high 2026-10-01

# List tasks
./build/task_app list

# Filter by priority
./build/task_app list high

# Mark a task as complete
./build/task_app complete 0

# Update title, priority, and due date
./build/task_app update 0 "Prepare production release" high 2026-10-05

# Clear a due date with `none`
./build/task_app update 0 "Prepare production release" high none

# Show overdue tasks for a reference date
./build/task_app overdue 2026-10-06
```

Legacy task records remain readable. New records include the optional due date while preserving existing completion and priority data.

## Testing

```bash
cd build
ctest --output-on-failure
```

## Documentation

To generate the API documentation:

```bash
cmake --build build --target docs
```

The output will be in `docs/generated/html`.

## Project Structure

- `include/`: Header files (Library API)
- `src/`: Implementation files and CLI main
- `tests/`: Unit tests
- `data/`: Data storage
- `docs/`: Documentation and landing page
- `.github/`: CI/CD workflows
