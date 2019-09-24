#!/bin/bash

dat_files=(*.dat)
if [ -e ${dat_files[0]} ];
then mv *.dat GENERATED_files_dat/
fi

o_files=(*.o)
if [ -e ${o_files[0]} ];
then mv *.o GENERATED_files_objects/
fi

aux_files=(*.aux)
if [ -e ${aux_files[0]} ];
then mv *.aux GENERATED_files_latex/aux/
fi

dvi_files=(*.dvi)
if [ -e ${dvi_files[0]} ]
then mv *.dvi GENERATED_files_latex/dvi/
fi

eps_files=(*.eps)
if [ -e ${eps_files[0]} ]
then mv *.eps GENERATED_files_latex/eps/
fi

dot_files=(*.dot)
if [ -e ${dot_files[0]} ]
then mv *.dot GENERATED_files_latex/dot/
fi

psfrag_files=(*.psfrag)
if [ -e ${psfrag_files[0]} ]
then mv *.psfrag GENERATED_files_latex/psfrag/
fi

mpl_files=(*.mpl)
if [ -e ${mpl_files[0]} ]
then mv *.mpl GENERATED_files_maple/
fi

log_files=(*.log)
if [ -e ${log_files[0]} ]
then mv *.log GENERATED_files_log/
fi

gnu_files=(*.gnuplot)
if [ -e ${gnu_files[0]} ]
then mv *.gnuplot GENERATED_files_graphics/
fi

osg_files=(osg_*.cpp)
if [ -e ${osg_files[0]} ]
then
mv osg_*.cpp GENERATED_files_osg/cpp
mv osg_*.h GENERATED_files_osg/h
fi

osg_files=(solids_*.cpp)
if [ -e ${osg_files[0]} ]
then
mv solids_*.cpp GENERATED_files_osg/cpp
mv solids_*.h GENERATED_files_osg/h
fi

c_files=(*.c)
if [ -e ${c_files[0]} ]
then mv *.c GENERATED_files_process_c_h/
fi

h_files=(*.h)
if [ -e ${h_files[0]} ]
then mv *.h GENERATED_files_process_c_h/
fi

m_files=(*.m)
if [ -e ${m_files[0]} ]
then mv *.m GENERATED_files_matlab/
fi

#if [ -f GENERATED_files_matlab/environment.m ]
#then cp GENERATED_files_matlab/environment.m SOURCE_matlab/
#fi

ini_files=(*.ini)
if [ -e ${ini_files[0]} ]
then mv *.ini GENERATED_OSG_bin/
fi

#cp -R ./SOURCE_solids ./GENERATED_OSG_bin
#cp ./common/files_osg/axes.osg GENERATED_OSG_bin/axes.osg
#cp ./common/files_osg/ground.stl GENERATED_OSG_bin/ground.stl

rm -f aux_*.bash
rm -f replace.bash

