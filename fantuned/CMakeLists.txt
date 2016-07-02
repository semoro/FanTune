
set(CPP_FILES src/main.cpp)
set(HEADERS)

include_directories(../libfantune/includes)
add_executable(fantuned ${HEADERS} ${CPP_FILES})

target_link_libraries(fantuned fantune)
