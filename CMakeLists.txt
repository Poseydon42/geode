cmake_minimum_required(VERSION 3.22)

project(Geode)

add_subdirectory(ThirdParty/glm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(SOURCES
        Source/main.cpp
        Source/TGAWriter.cpp
        Source/TGAWriter.h
)

add_executable(Geode ${SOURCES})
target_link_libraries(Geode PUBLIC glm)

# Enable all warnings and treat them as errors
if(MSVC)
	target_compile_options(Geode PRIVATE /W4 /WX)
else()
	target_compile_options(Geode PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

