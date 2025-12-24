cmake_minimum_required(VERSION "3.19.2")

project(ClassicLineEditor)
set(CMAKE_CXX_STANDARD 17)
add_executable(ClassicLineEditor "src/main.cpp" "src/LineData.cpp" "src/FileHandler.cpp" "src/CommandHandler.cpp")
target_include_directories(ClassicLineEditor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")