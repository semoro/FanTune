
set(CPP_FILES src/Fan.cpp src/FanCurve.cpp src/FanTest.cpp src/FanSelector.cpp)
set(HEADERS includes/Fan.h includes/FanCurve.h includes/FanTest.h includes/FanSelector.h)
include_directories(includes)
add_library(fantune SHARED ${HEADERS} ${CPP_FILES})
target_link_libraries(fantune sensors)
target_link_libraries(fantune udev)