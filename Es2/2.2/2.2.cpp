//Numerical Simulation Laboratory
//Exercise 2.2
//Made by Tommaso Rovelli 944280

#include "randomwalk.h"
#include "random.h"
#include "func.h"
#include <fstream>

int main(int argc, char* argv[]) {

	Random rnd;
	rnd.Init();

	double a=1;																	//lenght of the rw step
	int dim=3;																	//dimension of the rw
	int n_steps=100;															//number of steps of a rw
	int n_blocks=100;															//number of block
	int rw_per_block=100;														//number of rw per block

	std::vector<double> block_ave_lattice(n_steps);

	std::vector<double> ave_lattice(n_steps);
	std::vector<double> ave2_lattice(n_steps);

	std::vector<double> block_ave_continuum(n_steps);

	std::vector<double> ave_continuum(n_steps);
	std::vector<double> ave2_continuum(n_steps);

	std::vector<double> err_lattice(n_steps);
	std::vector<double> err_continuum(n_steps);

	RandomWalk rw_lattice(a,dim);
	RandomWalk rw_continuum(a,dim);

	for(int i=0;i<n_blocks;++i) {

		std::fill(block_ave_lattice.begin(), block_ave_lattice.end(), 0);		//reinizializing the data vector
		std::fill(block_ave_continuum.begin(), block_ave_continuum.end(), 0);

		for(int j=0;j<rw_per_block;++j) {

			for(int k=0; k< n_steps; ++k) {

				rw_lattice.LatticeStep(rnd);									//running the random walk for n_steps
				rw_continuum.Continuum3DStep(rnd);
			}

			block_ave_lattice += (rw_lattice.GetDistanceHistory()^2);			//I oveloaded some operators to implement basic vector algebra
			block_ave_continuum += (rw_continuum.GetDistanceHistory()^2);

			rw_lattice.Restart();												//restarting the rw
			rw_continuum.Restart();

		}

		ave_lattice +=  (block_ave_lattice/rw_per_block);
		ave2_lattice += (block_ave_lattice/rw_per_block)^2;

		ave_continuum += (block_ave_continuum/rw_per_block);
		ave2_continuum += (block_ave_continuum/rw_per_block)^2;

	}

	ave_lattice = ave_lattice/n_blocks;
	ave2_lattice = ave2_lattice/n_blocks;

	err_lattice = ( (ave2_lattice - (ave_lattice^2))/(n_blocks-1) )^0.5;

	ave_continuum = ave_continuum/n_blocks;
	ave2_continuum = ave2_continuum/n_blocks;

	err_continuum = ( (ave2_continuum - (ave_continuum^2))/(n_blocks-1) )^0.5;

	std::ofstream f("output_lat_2.2.out");										//print the data on files
	std::ofstream g("output_con_2.2.out");

	f << n_steps+1 << std::endl;
	g << n_steps+1 << std::endl;

	f << 0 << " " << 0 << std::endl;
	g << 0 << " " << 0 << std::endl;

	for(int i=0; i<n_steps; ++i) {

		f << std::sqrt(ave_lattice[i]) << " " << 1/(2*std::sqrt(ave_lattice[i]) ) * err_lattice[i]<< std::endl;
		g << std::sqrt(ave_continuum[i]) << " " << 1/(2*std::sqrt(ave_continuum[i]) ) * err_continuum[i] << std::endl;

	}

	f.close();
	g.close();

	return 0;

}