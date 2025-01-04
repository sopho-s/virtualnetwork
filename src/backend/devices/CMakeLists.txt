add_library(devices
    device.h
    echo.h
    echo.cpp
)
target_link_libraries(devices PRIVATE interfaces data)