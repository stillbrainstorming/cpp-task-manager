cmake_minimum_required(VERSION 3.14)
project(TaskManagerApp VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

add_library(TaskManagerLib
    src/Task.cpp
    src/TaskManager.cpp
    src/FileTaskRepository.cpp
    src/TaskService.cpp
)

target_include_directories(TaskManagerLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_executable(task_app src/main.cpp)
target_link_libraries(task_app PRIVATE TaskManagerLib nlohmann_json::nlohmann_json)

enable_testing()
add_executable(test_task tests/test_task.cpp)
target_link_libraries(test_task PRIVATE TaskManagerLib)
add_test(NAME TaskTest COMMAND test_task)

add_executable(test_persistence tests/test_persistence.cpp)
target_link_libraries(test_persistence PRIVATE TaskManagerLib)
add_test(NAME PersistenceTest COMMAND test_persistence)

add_executable(test_lifecycle tests/test_lifecycle.cpp)
target_link_libraries(test_lifecycle PRIVATE TaskManagerLib)
add_test(NAME LifecycleTest COMMAND test_lifecycle)

add_executable(test_service tests/test_service.cpp)
target_link_libraries(test_service PRIVATE TaskManagerLib)
add_test(NAME ServiceTest COMMAND test_service)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

install(TARGETS task_app TaskManagerLib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)
