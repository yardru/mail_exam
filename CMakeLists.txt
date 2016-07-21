cmake_minimum_required(VERSION 2.8)
project(final)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lstdc++")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(BOOST_LIBRARYDIR "$BOOST_LIBRARYDIR;/usr/lib/x86_64-linux-gnu")
find_package(Boost COMPONENTS system filesystem thread REQUIRED)

set(SOURCE_FILES main.cpp def.h def.cpp server.cpp server.h handler.cpp handler.h)
add_executable(final ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
