cmake_minimum_required(VERSION 3.10)
project(SetIterables VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Create executables
add_executable(main main.cpp)
add_executable(basic_examples basic_examples.cpp)
add_executable(advanced_examples advanced_examples.cpp)

# Set target properties
set_target_properties(main basic_examples advanced_examples
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Add custom target to run all examples
add_custom_target(run_all
    COMMAND echo "Running basic examples..."
    COMMAND $<TARGET_FILE:basic_examples>
    COMMAND echo "\\n\\nRunning advanced examples..."
    COMMAND $<TARGET_FILE:advanced_examples>
    DEPENDS basic_examples advanced_examples
    COMMENT "Running all example programs"
)

# Add custom target to run interactive demo
add_custom_target(demo
    COMMAND $<TARGET_FILE:main>
    DEPENDS main
    COMMENT "Running interactive demonstration"
)

# Install targets (optional)
install(TARGETS main basic_examples advanced_examples
    RUNTIME DESTINATION bin
)

install(FILES set_iterables.hpp
    DESTINATION include
)

# Print build information
message(STATUS "Project: ${PROJECT_NAME} ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")