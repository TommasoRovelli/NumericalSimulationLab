//Made by Tommaso Rovelli 944280

#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <fstream> 
#include <vector>
#include <cmath>
#include <iostream>
#include "random.h"

void operator+=(std::vector<double>&, std::vector<double>);
std::vector<double> operator/(std::vector<double>,double);
std::vector<double> operator^(std::vector<double>,double);
std::vector<double> operator+(std::vector<double>, std::vector<double>);
std::vector<double> operator-(std::vector<double>, std::vector<double>);

std::vector<double> SquaredVector(std::vector<double> vec);
std::vector<double> CumulativeAve (std::vector<double> vec);
std::vector<double> Error(std::vector<double> vec);
std::vector<double> Blocks(std::vector<double> vec, int n_blocks);

std::vector<double> AveVectorUD(Random &rndm, int M, int N);
std::vector<double> AveVectorExp(Random &rndm, int M, int N, double lambda);
std::vector<double> AveVectorCL(Random &rndm, int M, int N, double gamma, double mean);
std::vector<double> StdvVectorUD(Random &rndm, int M, int N, double theoric_mean);
std::vector<double> ChiSquared(Random &rnd, int N_bins, int N_throws, int N_times);


#endif 