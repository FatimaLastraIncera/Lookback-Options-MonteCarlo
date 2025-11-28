cmake_minimum_required(VERSION 3.10)
project(LookbackOptionsMonteCarlo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include folder
include_directories(include)

# Source files
add_executable(lookback_pricer
    src/main.cpp
    src/MonteCarlo.cpp
    src/LookbackPricer.cpp
    src/Greeks.cpp
)
