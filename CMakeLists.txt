cmake_minimum_required(VERSION 3.20)

project(obs-usukawa)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "${QTDIR}")

find_package(LibObs REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Boost REQUIRED COMPONENTS filesystem random)

file(GLOB usukawa_src
    "src/*.cpp"
    "src/*.hpp"
    "src/message-handler-components/*.cpp"
    "src/message-handler-components/*.hpp"
)

add_library(
    obs-usukawa MODULE
    ${usukawa_src}
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
