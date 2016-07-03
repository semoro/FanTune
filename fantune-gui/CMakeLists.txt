
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

set(CPP_FILES src/main.cpp src/mainwindow.cpp)
set(HEADERS src/mainwindow.h)
include_directories(includes)
add_executable(fantune-gui ${HEADERS} ${CPP_FILES})

qt5_use_modules(fantune-gui Widgets)