// g++ gaussian_filter.cpp -std=c++11 -Wall -o gaussian_filter -I/usr/include/python2.7 -lpython2.7
/* C++ Related */
#include <iostream>
#include <stdio.h>
#include <math.h> 
#include "matplotlib-cpp/matplotlibcpp.h"

namespace plt = matplotlibcpp;

double fwhm2sigma(float fwhm)
{
    double sigma = fwhm / (sqrt(8*log(2)));
    return sigma;
}

double sigma2fwhm(float sigma)
{
    double fwhm = sigma * (sqrt(8*log(2)));
    return fwhm;
}

std::vector<double> computeKernel(int n_points, int x_position, std::vector<double> x_values, double fwhm)
{
    //Compute the kernel for the given x point
    std::vector<double> kernel(n_points);
    double sigma  = fwhm2sigma(fwhm);
    double sum_kernel = 0;
    for (int i =0; i<n_points;i++)
    {
        //Compute gaussian kernel
        kernel[i] = exp(-(pow(x_values[i] - x_position,2) / (2*pow(sigma,2))));
        //compute a weight for each kernel position
        sum_kernel += kernel[i];
    }
    //apply weight to each kernel position to give more important value to the x that are around ower x
    for(int i = 0;i<n_points;i++)
        kernel[i] = kernel[i] / sum_kernel;
    return kernel;
}

double applyKernel(int n_points, int x_position, std::vector<double> kernel, std::vector<double> y_values)
{
    std::vector<double> smoothed_vals(n_points);
    double y_filtered = 0;
    //apply filter to all the y values with the weighted kernel
    for(int i = 0;i<n_points;i++) 
        y_filtered += kernel[i] * y_values[i];

    //store the filtered value for this x_postions
    smoothed_vals[x_position] = y_filtered;
    return y_filtered;
}

int main()
{
    int n_points = 50; //number of points
    double fwhm = 2; //FWHM
    std::vector<double> x_values(n_points);
    //Initiate x array with values from 0 -> n_points
    for (int i = 0;i<n_points;i++)
        x_values[i] = i;
    std::vector<double> y_values(n_points);
    //Initiate y array with random values
    for (int i = 0;i<n_points;i++)
        y_values[i] = std::rand() % 10;

    std::vector<double> y_values_filtered(n_points);

    plt::figure_size(1200, 780);

    //apply filter to every points
    for (int x_position=0;x_position<n_points;x_position++)
    {
        std::vector<double> kernel(n_points);
        kernel = computeKernel(n_points,x_position,x_values,fwhm);
        double y_filtered = applyKernel(n_points, x_position,kernel,y_values);
        y_values_filtered[x_position] = y_filtered;
    }
    plt::plot(x_values, y_values,"r");
    plt::plot(x_values, y_values_filtered);
    plt::show();

}

