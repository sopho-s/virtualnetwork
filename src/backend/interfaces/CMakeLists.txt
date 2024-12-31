add_library(interfaces endpoint.h endpoint.cpp NIC.h NIC.cpp)
target_link_libraries(interfaces PRIVATE data)