add_library(interfaces endpoint.h NIC.h NIC.cpp)
target_link_libraries(interfaces PRIVATE data)