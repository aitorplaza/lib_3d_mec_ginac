
dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT(lib_3d_mec_ginac/lib_3d_mec_ginac.h)
AM_CONFIG_HEADER(config.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

LIB3D_MEC_GINAC_LIBRARY_NAME=lib_3d_mec_ginac

#release versioning
LIB3D_MEC_GINAC_MAJOR_VERSION=2
LIB3D_MEC_GINAC_MINOR_VERSION=0
LIB3D_MEC_GINAC_MICRO_VERSION=0

#API version (often = LIB3D_MEC_GINAC_MAJOR_VERSION.LIB3D_MEC_GINAC_MINOR_VERSION)
GENERIC_API_VERSION=$LIB3D_MEC_GINAC_MAJOR_VERSION.$LIB3D_MEC_GINAC_MINOR_VERSION
AC_SUBST(GENERIC_API_VERSION)

#shared library versioning
LIB3D_MEC_GINAC_LIBRARY_VERSION=$LIB3D_MEC_GINAC_MAJOR_VERSION:$LIB3D_MEC_GINAC_MINOR_VERSION:$LIB3D_MEC_GINAC_MICRO_VERSION
#                       | | |
#                +------+ | +---+
#                |        |     |
#             current:revision:age
#                |        |     |
#                |        |     +- increment if interfaces have been added
#                |        |        set to zero if interfaces have been removed
#                                  or changed
#                |        +- increment if source code has changed
#                |           set to zero if current is incremented
#                +- increment if interfaces have been added, removed or changed


dnl --------------------------------
dnl Package name and version number
dnl --------------------------------

AC_SUBST(LIB3D_MEC_GINAC_LIBRARY_VERSION)

PACKAGE=$LIB3D_MEC_GINAC_LIBRARY_NAME
AC_SUBST(LIB3D_MEC_GINAC_LIBRARY_NAME)

LIB3D_MEC_GINAC_VERSION=$LIB3D_MEC_GINAC_MAJOR_VERSION.$LIB3D_MEC_GINAC_MINOR_VERSION.$LIB3D_MEC_GINAC_MICRO_VERSION
LIB3D_MEC_GINAC_RELEASE=$LIB3D_MEC_GINAC_MAJOR_VERSION.$LIB3D_MEC_GINAC_MINOR_VERSION
AC_SUBST(LIB3D_MEC_GINAC_RELEASE)
AC_SUBST(LIB3D_MEC_GINAC_VERSION)

VERSION=$LIB3D_MEC_GINAC_VERSION

AM_INIT_AUTOMAKE($PACKAGE, $VERSION, no-define)

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

AC_PROG_CC
AC_PROG_CXX
AM_PROG_LIBTOOL
AM_SANITY_CHECK

AC_LANG_CPLUSPLUS

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile \
          lib_3d_mec_ginac.pc \
          lib_3d_mec_ginac/Makefile \
)

