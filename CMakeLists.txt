cmake_minimum_required(VERSION 3.20)

project(obs-usukawa)

set(CMAKE_PREFIX_PATH "${QTDIR}")

find_package(LibObs REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

add_library(
    obs-usukawa MODULE
    src/plugin.cpp
    src/plugin.hpp
)

include_directories(
)

target_link_libraries(
    obs-usukawa
    libobs
    Qt5::Core
    Qt5::Widgets
)
