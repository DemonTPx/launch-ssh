cmake_minimum_required(VERSION 3.5)
project(launch_ssh)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
    set(wxWidgets_ROOT_DIR C:/wx)
    set(wxWidgets_LIB_DIR C:/wx/lib/gcc810_x64_dll)
    set(wxWidgets_EXCLUDE_COMMON_LIBRARIES true)

    set(CMAKE_EXE_LINKER_FLAGS -mwindows)
ENDIF()

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(launch_ssh src/resources.rc src/App.cpp src/MainFrame.cpp src/HistoryFile.cpp src/strnatcmp.c)
target_link_libraries(launch_ssh ${wxWidgets_LIBRARIES})
