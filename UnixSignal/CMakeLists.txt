cmake_minimum_required(VERSION 3.25)
project(UnixSignal LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(UNIXSIGNAL_INCLUDES include/)
set(UNIXSIGNAL_SOURCES src/UnixSignal.cpp include/UnixSignal.hpp)

add_executable(${PROJECT_NAME} main.cpp ${UNIXSIGNAL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${UNIXSIGNAL_INCLUDES})
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)
