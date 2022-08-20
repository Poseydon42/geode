cmake_minimum_required(VERSION 3.22)

project(Geode)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(SOURCES
    Source/main.cpp
)

add_executable(Geode ${SOURCES})

# Enable all warnings and treat them as errors
if(MSVC)
	target_compile_options(Geode PRIVATE /W4 /WX)
else()
	target_compile_options(Geode PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

