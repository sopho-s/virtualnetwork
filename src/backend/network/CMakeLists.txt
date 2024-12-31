add_library(network network.h network.cpp)
target_link_libraries(network PRIVATE interfaces data)