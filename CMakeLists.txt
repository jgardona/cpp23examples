cmake_minimum_required(VERSION 3.16)

project(cpp23examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(formatex formatex.cpp)
add_executable(pairex pairex.cpp)
add_executable(ranges ranges.cpp)
add_executable(casts casts.cpp)
add_executable(exceptions exceptions.cpp)
add_executable(string_view_ex string_view_ex.cpp)
add_executable(file_processing file_processing.cpp)
add_executable(types types.cpp)

include(GNUInstallDirs)
install(TARGETS formatex
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
