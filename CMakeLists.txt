cmake_minimum_required(VERSION 3.14)
project(TaskManagerApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ---
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# --- Library ---
add_library(TaskManagerLib
    src/Task.cpp
    src/TaskManager.cpp
)

target_include_directories(TaskManagerLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# --- Executable ---
add_executable(task_app src/main.cpp)
target_link_libraries(task_app PRIVATE TaskManagerLib nlohmann_json::nlohmann_json)

# --- Testing ---
enable_testing()
add_executable(test_task tests/test_task.cpp)
target_link_libraries(test_task PRIVATE TaskManagerLib)
add_test(NAME TaskTest COMMAND test_task)

# --- Doxygen Documentation ---
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # If Doxyfile.in doesn't exist, we can use a basic one or configure it
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

# --- Installation ---
install(TARGETS task_app TaskManagerLib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)
