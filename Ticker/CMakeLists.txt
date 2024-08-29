cmake_minimum_required(VERSION 3.25)

project(Ticker LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(Ticker main.cpp
    Ticker.hpp Ticker.cpp)
target_link_libraries(Ticker Qt${QT_VERSION_MAJOR}::Core)
