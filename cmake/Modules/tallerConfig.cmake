INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_TALLER taller)

FIND_PATH(
    TALLER_INCLUDE_DIRS
    NAMES taller/api.h
    HINTS $ENV{TALLER_DIR}/include
        ${PC_TALLER_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    TALLER_LIBRARIES
    NAMES gnuradio-taller
    HINTS $ENV{TALLER_DIR}/lib
        ${PC_TALLER_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TALLER DEFAULT_MSG TALLER_LIBRARIES TALLER_INCLUDE_DIRS)
MARK_AS_ADVANCED(TALLER_LIBRARIES TALLER_INCLUDE_DIRS)

