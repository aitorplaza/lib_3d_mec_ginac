cmake_minimum_required(VERSION 3.10)
project(lib_3d_mec_ginac VERSION 2.0.0 LANGUAGES CXX)

# Enable C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find pkg-config packages (GiNaC, CLN, GSL, BLAS, LAPACK)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GINAC REQUIRED IMPORTED_TARGET ginac)
pkg_check_modules(CLN REQUIRED IMPORTED_TARGET cln)
pkg_check_modules(GSL REQUIRED IMPORTED_TARGET gsl)
pkg_check_modules(BLAS REQUIRED IMPORTED_TARGET blas)
pkg_check_modules(LAPACK REQUIRED IMPORTED_TARGET lapack)

# Define source files
set(SOURCE_FILES
    lib_3d_mec_ginac/Base.cc
    lib_3d_mec_ginac/Drawing3D.cc
    lib_3d_mec_ginac/Frame.cc
    lib_3d_mec_ginac/Globals.cc
    lib_3d_mec_ginac/Matrix.cc
    lib_3d_mec_ginac/Point.cc
    lib_3d_mec_ginac/Solid.cc
    lib_3d_mec_ginac/System.cc
    lib_3d_mec_ginac/Tensor3D.cc
    lib_3d_mec_ginac/Vector3D.cc
    lib_3d_mec_ginac/VectorE.cc
    lib_3d_mec_ginac/Wrench3D.cc
    lib_3d_mec_ginac/atom.cc
    lib_3d_mec_ginac/symbol_numeric.cc
)

# Define header files to install
set(HEADER_FILES
    lib_3d_mec_ginac/Base.h
    lib_3d_mec_ginac/Drawing3D.h
    lib_3d_mec_ginac/Frame.h
    lib_3d_mec_ginac/Globals.h
    lib_3d_mec_ginac/Matrix.h
    lib_3d_mec_ginac/Point.h
    lib_3d_mec_ginac/Solid.h
    lib_3d_mec_ginac/System.h
    lib_3d_mec_ginac/Tensor3D.h
    lib_3d_mec_ginac/Vector3D.h
    lib_3d_mec_ginac/VectorE.h
    lib_3d_mec_ginac/Wrench3D.h
    lib_3d_mec_ginac/atom.h
    lib_3d_mec_ginac/lib_3d_mec_ginac.h
    lib_3d_mec_ginac/symbol_numeric.h
)

# Create the dynamic library (SHARED)
add_library(lib_3d_mec_ginac SHARED ${SOURCE_FILES})

# Ensure POSITION_INDEPENDENT_CODE is ON (required for shared libs)
set_target_properties(lib_3d_mec_ginac PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    VERSION ${PROJECT_VERSION}
    SOVERSION 2
    OUTPUT_NAME "_3d_mec_ginac"  # Generates lib_3d_mec_ginac.so (linked as -l_3d_mec_ginac)
)

# Link dependency libraries
target_link_libraries(lib_3d_mec_ginac PRIVATE
    PkgConfig::GINAC
    PkgConfig::CLN
    PkgConfig::GSL
    PkgConfig::BLAS
    PkgConfig::LAPACK
)

# Include directories
target_include_directories(lib_3d_mec_ginac PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Installation rules
include(GNUInstallDirs)

install(TARGETS lib_3d_mec_ginac
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES ${HEADER_FILES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lib_3d_mec_ginac
)
