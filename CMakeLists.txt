cmake_minimum_required(VERSION 3.5)
project(dropcopycpp)
set(CMAKE_CXX_STANDARD 11)

set(BINARY ${CMAKE_PROJECT_NAME})
# Include the current directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall ")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W ")


# Add all source files in the current directory to the SOURCES variable
#file(GLOB_RECURSE SOURCES  *.hpp *.cpp *.h)


find_package(OpenSSL REQUIRED)

# Add the executable target
add_executable(${BINARY}  
basesocket.hpp
Constants.h
CharBuf.h
CharBuf.cpp
tcpsocket.hpp
tcp-client.cpp
structs.hpp    
)

target_link_libraries(${BINARY} PUBLIC  OpenSSL::SSL pthread)