#!/bin/bash

cp state_woh.dat state.dat
cp ./GENERATED_files_graphics/*.gnuplot .

if [ -f coordinates.gnuplot ]
then gnuplot coordinates.gnuplot
mv coordinates.eps GENERATED_files_graphics/
mv coordinates.gnuplot GENERATED_files_graphics/
fi

if [ -f velocities.gnuplot ]
then gnuplot velocities.gnuplot
mv velocities.eps GENERATED_files_graphics/
mv velocities.gnuplot GENERATED_files_graphics/
fi

if [ -f accelerations.gnuplot ]
then gnuplot accelerations.gnuplot
mv accelerations.eps GENERATED_files_graphics/
mv accelerations.gnuplot GENERATED_files_graphics/
fi

if [ -f joint_unknowns.gnuplot ]
then gnuplot joint_unknowns.gnuplot
mv joint_unknowns.eps GENERATED_files_graphics/
mv joint_unknowns.gnuplot GENERATED_files_graphics/
fi


