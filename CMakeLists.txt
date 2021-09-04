cmake_minimum_required(VERSION 3.20)

project(obs-usukawa)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "${QTDIR}")

find_package(LibObs REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Boost REQUIRED COMPONENTS filesystem random)

add_library(
    obs-usukawa MODULE
    src/plugin.cpp
    src/plugin.hpp
    src/usukawa-core.cpp
    src/usukawa-core.hpp
    src/websocket-client.cpp
    src/websocket-client.hpp
    src/message-handler.cpp
    src/message-handler.hpp
)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${WEBSOCKETPP_ROOT}
)

target_link_libraries(
    obs-usukawa
    libobs
    Qt5::Core
    Qt5::Widgets
    Boost::filesystem
    Boost::random
)
