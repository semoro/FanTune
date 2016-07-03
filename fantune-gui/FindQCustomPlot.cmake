# Try to find the QCustomPlot library
#  QCUSTOMPLOT_FOUND - system has QCustomPlot lib
#  QCUSTOMPLOT_INCLUDE_DIRS - the include directories needed
#  QCUSTOMPLOT_LIBRARIES - libraries needed

FIND_PATH(QCUSTOMPLOT_INCLUDE_DIR NAMES qcustomplot.h)
FIND_LIBRARY(QCUSTOMPLOT_LIBRARY NAMES qcustomplot)

SET(QCUSTOMPLOT_INCLUDE_DIRS ${QCUSTOMPLOT_INCLUDE_DIR})
SET(QCUSTOMPLOT_LIBRARIES ${QCUSTOMPLOT_LIBRARY})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QCUSTOMPLOT DEFAULT_MSG QCUSTOMPLOT_LIBRARY QCUSTOMPLOT_INCLUDE_DIR)

MARK_AS_ADVANCED(QCUSTOMPLOT_INCLUDE_DIR QCUSTOMPLOT_LIBRARY)
