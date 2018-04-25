cmake_minimum_required(VERSION 3.5)
project(launch_ssh)

set(CMAKE_CXX_STANDARD 11)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(launch_ssh src/App.cpp src/MainFrame.cpp src/HistoryFile.cpp src/strnatcmp.c)
target_link_libraries(launch_ssh ${wxWidgets_LIBRARIES})
