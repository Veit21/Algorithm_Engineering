cmake_minimum_required(VERSION 3.23)
project(simulated_annealing LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

# search for OpenMP
find_package(OpenMP REQUIRED)

# save the sources as a variable
set(SOURCES
        src/Main.cpp
        src/IO.cpp src/MathUtil.cpp src/Shape.cpp src/SimulatedAnnealing.cpp
        src/Different_Shapes/Bullseye.cpp src/Different_Shapes/Circle.cpp
        src/Different_Shapes/Dots.cpp src/Different_Shapes/LineShape.cpp
        )

# create executable
add_executable(simulated_annealing ${SOURCES})

# include directory 'include' for the header files
target_include_directories(simulated_annealing PUBLIC include)

# link libraries
target_link_libraries(simulated_annealing PUBLIC OpenMP::OpenMP_CXX)

# set compiler flags
target_compile_options(simulated_annealing PRIVATE -Ofast -march=native)