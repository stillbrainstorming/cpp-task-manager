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
cmake -S . -B build
cmake --build build
```

### Usage

```bash
./build/task_app add "Prepare release" high 2026-10-01
./build/task_app list
./build/task_app list high
./build/task_app complete 0
./build/task_app update 0 "Prepare production release" high 2026-10-05
./build/task_app update 0 "Prepare production release" high none
./build/task_app overdue 2026-10-06
```

Legacy task records remain readable. New records include the optional due date while preserving existing completion and priority data.

## Testing

```bash
cd build
ctest --output-on-failure
```

The test suite covers task construction and serialization, lifecycle and persistence boundaries, priority and overdue filtering, and service-level orchestration including invalid-operation behavior.

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
