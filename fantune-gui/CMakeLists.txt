
set(CPP_FILES src/main.cpp)
set(HEADERS)
include_directories(includes)
add_library(fantune-gui ${HEADERS} ${CPP_FILES})
