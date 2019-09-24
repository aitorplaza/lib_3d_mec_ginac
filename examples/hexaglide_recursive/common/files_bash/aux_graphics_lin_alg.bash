#!/bin/bash

if [ -f coordinates.gnuplot ]
then gnuplot coordinates.gnuplot
mv coordinates.eps GENERATED_files_graphics/coordinates_lin_alg.eps
fi

if [ -f velocities.gnuplot ]
then gnuplot velocities.gnuplot
mv velocities.eps GENERATED_files_graphics/velocities_lin_alg.eps
fi

if [ -f accelerations.gnuplot ]
then gnuplot accelerations.gnuplot
mv accelerations.eps GENERATED_files_graphics/accelerations_lin_alg.eps
fi

if [ -f joint_unknowns.gnuplot ]
then gnuplot joint_unknowns.gnuplot
mv joint_unknowns.eps GENERATED_files_graphics/joint_unknowns_lin_alg.eps
fi

rm state.dat
