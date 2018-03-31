cmake_minimum_required (VERSION 2.6)

project (test-pthread)
#SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_THREAD_PREFER_PTHREAD On)
set (THREADS_PREFER_PTHREAD_FLAG TRUE)
SET (GCC_COVERAGE_COMPILE_FLAGS "-g -Wall")
#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
find_package(Threads REQUIRED)
add_executable(test-pthread main.cc)
target_link_libraries (test-pthread pthread)




project (test-std)
#SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_THREAD_PREFER_PTHREAD Off)
set (THREADS_PREFER_PTHREAD_FLAG FALSE)
SET (GCC_COVERAGE_COMPILE_FLAGS "-g -Wall")
#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
add_executable(test-std main.cc)
target_link_libraries (test-std Threads::Threads)


