
set(CPP_FILES src/Fan.cpp src/FanCurve.cpp src/FanTest.cpp)
set(HEADERS includes/Fan.h includes/FanCurve.h includes/FanTest.h)
include_directories(includes)
add_library(fantune SHARED ${HEADERS} ${CPP_FILES})
target_link_libraries(fantune sensors)
target_link_libraries(fantune udev)