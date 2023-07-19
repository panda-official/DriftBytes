add_executable(
    unit_tests
    bytes_test.cc
)

target_link_libraries(unit_tests PRIVATE ${PROJECT_NAME})
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

# to test internal classes
target_include_directories(
    unit_tests
    PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/sources
)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

# Code coverage
option(CODE_COVERAGE "Enable coverage report (only for debug build type)" OFF)

if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        target_compile_options(unit_tests PRIVATE --coverage)
        target_link_options(unit_tests PRIVATE --coverage)
        message(STATUS "Turn on code coverage")
    else(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(
            WARNING
            "Code coverage only works with Debug build type. Skipping"
        )
    endif(CMAKE_BUILD_TYPE STREQUAL Debug)
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)