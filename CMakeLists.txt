cmake_minimum_required(VERSION 3.16)

project(drift_bytes VERSION 0.1.0 LANGUAGES CXX)

option(DB_BUILD_TESTS "Enable unit tests" OFF)

find_package(Cereal REQUIRED)

set(TARGET_NAME ${PROJECT_NAME})
add_library(${TARGET_NAME} INTERFACE)

add_library(${TARGET_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

link_libraries(${TARGET_NAME} cereal::cereal)

set_target_properties(
    ${TARGET_NAME}
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
)

target_include_directories(
    ${TARGET_NAME}
    INTERFACE
        ${cereal_INCLUDE_DIRS}
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(DB_BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Install rules
include(GNUInstallDirs)

## Create package targets file
install(TARGETS ${TARGET_NAME} EXPORT ${TARGET_NAME}-target)
install(
    EXPORT ${TARGET_NAME}-target
    FILE ${TARGET_NAME}-targets.cmake
    NAMESPACE ${TARGET_NAME}::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

include(CMakePackageConfigHelpers)

# Create package config file
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
    "${TARGET_NAME}-config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)
# Create package version file
write_basic_package_version_file(
    ${TARGET_NAME}-config-version.cmake
    COMPATIBILITY ExactVersion
)

# Install cmake files
install(
    FILES
        "${PROJECT_BINARY_DIR}/${TARGET_NAME}-config.cmake"
        "${PROJECT_BINARY_DIR}/${TARGET_NAME}-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# Install headers
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/drift_bytes
    TYPE INCLUDE
    PATTERN "*.md"
    EXCLUDE
)

install(TARGETS ${TARGET_NAME} INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
