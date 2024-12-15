cmake_minimum_required(VERSION 3.10)
project(AirlineReservation VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/main.cpp
    src/airline_system.cpp
)

# Add header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create executable
add_executable(airline ${SOURCES})

# Add compiler warnings
if(MSVC)
    target_compile_options(airline PRIVATE /W4)
else()
    target_compile_options(airline PRIVATE -Wall -Wextra -pedantic)
endif()