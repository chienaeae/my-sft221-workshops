cmake_minimum_required(VERSION 3.5.0)

project(code LANGUAGES C CXX)

# The CMAKE_EXPORT_COMPILE_COMMANDS option enables generation of a compile_commands.json file containing the exact
# compiler calls for all translation units of the project in machine-readable form. This is useful for tools that need
# to analyze or replicate the build.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(include)

add_executable(main src/main.c)
add_library(lib STATIC src/lib/stringhelp.c)
add_library(log4c STATIC src/log4c/log4c.c)

file(GLOB TEST_SOURCES test/*.cpp)
add_executable(mainTests test/lib_test.cpp)

# Here to find package
find_package(GTest CONFIG REQUIRED)

# Set compile features for C
target_compile_features(main PRIVATE c_std_99)
target_compile_features(lib PRIVATE c_std_99)
target_compile_features(log4c PRIVATE c_std_99)

# Set compile features for C++ tests
target_compile_features(mainTests PRIVATE cxx_std_14)

# Here to link libraries
target_link_libraries(main PRIVATE lib log4c)
target_link_libraries(lib PRIVATE log4c)
target_link_libraries(mainTests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        lib)

include(GoogleTest)
gtest_discover_tests(mainTests)
