cmake_minimum_required(VERSION "3.19.2")

project(ClassicLineEditor)
set(CMAKE_CXX_STANDARD 17)

add_library(EditorClasses STATIC "src/LineData.cpp" "src/FileHandler.cpp" "src/CommandHandler.cpp")
add_executable(ClassicLineEditor "src/main.cpp")
target_link_libraries(ClassicLineEditor PRIVATE EditorClasses)
target_include_directories(ClassicLineEditor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_executable(TESTS_ClassicLineEditor "tests/TESTS_LineData.cpp" "tests/TESTS_FileHandler.cpp" "tests/TESTS_CommandHandler.cpp")
target_link_libraries(TESTS_ClassicLineEditor PRIVATE EditorClasses)
target_include_directories(TESTS_ClassicLineEditor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

install(TARGETS ClassicLineEditor)