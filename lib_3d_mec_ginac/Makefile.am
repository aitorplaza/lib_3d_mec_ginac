## Source directory

##SUBDIRS = sub

h_sources = Drawing3D.h Wrench3D.h Solid.h Matrix.h Point.h Frame.h System.h Vector3D.h Tensor3D.h Globals.h Base.h lib_3d_mec_ginac.h symbol_numeric.h atom.h VectorE.h
cc_sources = Drawing3D.cc Wrench3D.cc Solid.cc Matrix.cc Point.cc Frame.cc System.cc Vector3D.cc Tensor3D.cc Base.cc Globals.cc symbol_numeric.cc atom.cc VectorE.cc

library_includedir=$(includedir)/$(LIB3D_MEC_GINAC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES= lib_3d_mec_ginac-2.0.la
lib_3d_mec_ginac_2_0_la_SOURCES= $(h_sources) $(cc_sources)
##libexamplelib_2_0_la_LIBADD= sub/libsub.la
lib_3d_mec_ginac_2_0_la_LDFLAGS= -version-info $(LIB3D_MEC_GINAC_LIBRARY_VERSION) -release $(LIB3D_MEC_GINAC_RELEASE)

