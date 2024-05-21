cmake_minimum_required(VERSION 3.22.1)
project(SStudData)

# Установим стандарт C++ на C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Укажем директорию с заголовочными файлами
include_directories(include)

# Получим список всех исходных файлов
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Создадим исполняемый файл из всех найденных исходных файлов
add_executable(SStudData main.cpp ${SOURCES})

# Определение пользовательской команды для запуска скрипта мониторинга
find_program(NODE_EXECUTABLE node)
if(NOT NODE_EXECUTABLE)
    message(FATAL_ERROR "Node.js is required but was not found.")
endif()

add_custom_target(
    StartMonitor ALL
    COMMAND ${NODE_EXECUTABLE} "/home/silkfinik/VS\ Code/my_settings/monitor_files.js" SStudData
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Запуск мониторинга файлов для проекта SStudData"
)