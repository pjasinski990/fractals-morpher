cmake_minimum_required(VERSION 3.0)

project(Fractals VERSION 1.0 LANGUAGES CXX) 

include_directories(include)
add_library(lib src/MainFrame.cpp src/MainPanel.cpp src/MenuPanel.cpp src/Canvas.cpp)

find_package(wxWidgets REQUIRED core)
include(${wxWidgets_USE_FILE})

add_executable(Fractals apps/App.cpp)
target_link_libraries(Fractals lib ${wxWidgets_LIBRARIES})

add_compile_options(-g -pedantic -Wall -Wextra) 
