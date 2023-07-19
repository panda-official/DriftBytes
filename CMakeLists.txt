cmake_minimum_required(VERSION 3.16)

project(drift_bytes VERSION 0.1.0 LANGUAGES CXX)

option(DB_BUILD_TESTS "Enable unit tests" OFF)


find_package(Cereal REQUIRED)

add_library(
        ${PROJECT_NAME}
        INTERFACE)

link_libraries(
        ${PROJECT_NAME}
        cereal::cereal
)

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
target_include_directories(
        ${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${cereal_INCLUDE_DIRS}
)

if (DB_BUILD_TESTS)
    add_subdirectory(tests)
endif ()