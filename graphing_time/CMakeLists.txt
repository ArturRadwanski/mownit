cmake_minimum_required(VERSION 4.1)
project(graphing_time)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(graphing_time main.cpp)
target_link_libraries(graphing_time
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

