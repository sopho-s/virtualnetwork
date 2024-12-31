add_library(initializer
    initializer.cpp
    initializer.h
)
target_link_libraries(initializer PRIVATE data interfaces rapidxml)
