cmake_minimum_required(VERSION 3.10)

# Set the project name
project(virtualnetwork CXX)

# Add the executable
add_executable(virtualnetwork main.cpp)

# Add the subdirectories
add_subdirectory(backend)
add_subdirectory(imports)

# Link the library
target_link_libraries(virtualnetwork PRIVATE interfaces data initializer network)