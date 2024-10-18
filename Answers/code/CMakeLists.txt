cmake_minimum_required(VERSION 3.23)
project(exam_assignments LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

# add executables
add_executable(hello week_01/hello.cpp)
add_executable(manual_parallel week_01/manual_parallel.cpp)
add_executable(pi_parallel_w01 week_01/pi_parallel.cpp)
add_executable(pi_monte_carlo_parallel week_01/pi_monte_carlo_parallel.cpp)
add_executable(race_condition week_02/race_condition.cpp)
add_executable(unbalanced_workload week_02/unbalanced_workload.cpp)
add_executable(schedule_clause week_02/schedule_clause.cpp)
add_executable(continue_hack week_02/continue_hack.cpp)
add_executable(pi_parallel_w03 week_03/pi_parallel.cpp)
add_executable(pi_parallel_manual week_03/pi_parallel_manual.cpp)
add_executable(mandelbrot week_03/mandelbrot.cpp)
add_executable(merge_sort week_04/merge_sort.cpp)
add_executable(merge_parallel week_04/merge_parallel.cpp)

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -Ofast -march=native")