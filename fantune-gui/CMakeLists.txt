
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Qt5Widgets REQUIRED)
find_package(QCustomPlot REQUIRED)

find_package(Boost COMPONENTS System)

set(CPP_FILES src/main.cpp src/mainwindow.cpp src/settingswidget.cpp src/PlotPoint.cpp src/fanpreview.cpp src/main.h)
include_directories(${QCUSTOMPLOT_INCLUDE_DIRS} ../libfantune/includes src)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(fantune-gui ${CPP_FILES})
target_link_libraries(fantune-gui fantune)
target_link_libraries(fantune-gui rt)
target_link_libraries(fantune-gui ${QCUSTOMPLOT_LIBRARY})
target_link_libraries(fantune-gui ${Boost_LIBRARIES})
qt5_use_modules(fantune-gui Widgets)