//Made by Tommaso Rovelli 944280

#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <fstream> 
#include <vector>
#include <cmath>
#include <iostream>
#include "random.h"


std::vector<double> SquaredVector(std::vector<double> vec);
std::vector<double> CumulativeAve (std::vector<double> vec);
std::vector<double> Error(std::vector<double> vec);
std::vector<double> AveVectorUD(Random &rndm, int M, int N);
std::vector<double> StdvVectorUD(Random &rndm, int M, int N, double theoric_mean);
std::vector<double> ChiSquared(Random &rnd, int N_bins, int N_throws, int N_times);


#endif 