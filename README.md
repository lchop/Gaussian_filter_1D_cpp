# gaussian_filter_1D C++

Implementation of a gaussian filter 1D, also known as gaussian kernel smoother in c++.
https://en.wikipedia.org/wiki/Kernel_smoother

In this version the y values are random and the x values are set from 0-> n_points with a step of 1.
*Param*:
n_point: number of points

I am using the package matplotlib-cpp to plot the curves, a wrapper from https://github.com/lava/matplotlib-cpp.

*How to use ?*
I am using g++ compiler on Ubuntu 16.04.
In a terminal use the following to build the executable:
g++ gaussian_filter_1D.cpp -std=c++11 -Wall -o gaussian_filter_1D -I/usr/include/python2.7 -lpython2.7
When it is done type:
./gaussian_filter_1D
