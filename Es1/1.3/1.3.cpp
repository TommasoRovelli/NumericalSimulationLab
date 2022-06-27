//Numerical Simulation Laboratory
//Exercise 1.3
//Made by Tommaso Rovelli 944280

#include "buffon.h"
#include "func.h"
#include <fstream>

int main(int argc, char* argv[]) {

	Random rnd;
	rnd.Init();

	int throws_per_block = 1000;																//number of throws per block 
	int N_blocks = 100;																			//number of blocks

	double length = 1;																			//lenght of the needle
	double distance = 1.3;																		//distance between two lines

	Buffon buff(length, distance);

	std::vector<double> pi_extimation(buff.PiExtimationVector(N_blocks, throws_per_block,rnd));	//creating a set of extimation of pi, already in block form

	std::vector<double> cumulative_pi(CumulativeAve(pi_extimation));							//comulative mean and error
	std::vector<double> err_pi(Error(pi_extimation));

	std::ofstream f("output_pi_1.3.out");														//printing the data on file

	f << N_blocks << " " << throws_per_block << std::endl;

	for(int i=0; i<N_blocks; ++i) f << cumulative_pi[i] << " " << err_pi[i] << std::endl;

	f.close();

	return 0;


}