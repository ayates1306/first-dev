cmake_minimum_required (VERSION 2.6)

project (led-avs)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_THREAD_PREFER_PTHREAD On)
set (THREADS_PREFER_PTHREAD_FLAG TRUE)
SET (GCC_COVERAGE_COMPILE_FLAGS "-G -g -Wall -std-c++11 -pthread  -lpthread")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std-c++11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=c++11 -pthread -lpthread ")
set (CMAKE_SHARED_LINKER_FLAGS "-pthread -Wl,--as-needed")
#find_package(threads REQUIRED)
add_executable(led-avs src/main.cc)
target_link_libraries (led-avs pthread)



