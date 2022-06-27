//Numerical Simulation Laboratory
//Exercise 1.2
//Made by Tommaso Rovelli 944280

#include <fstream>
#include "func.h"

int main(int argc, char* argv[]) {

	Random rnd;

	std::vector<int> L = {1,2,10,100};							//dimensions of the block to show the convergence of some distributions to another (Central Limit Theorem)
	int N = 10000;												//number of throws
	int dim = L.size();

	double lambda = 1;											//lambda for the exponential distribution
	double mean = 0;											//mean of the Cauchy-Lorentz distribution
	double gamma = 1;											//gamma of the Chauchy-Lorentz distibution

	std::vector<std::vector<double>> UDAve_Vec(dim); 			//vectors of vectors, to record N elements for each block dimension
	std::vector<std::vector<double>> ExpAve_Vec(dim);			
	std::vector<std::vector<double>> CLAve_Vec(dim);

	for(int i=0; i<dim; ++i) {									//creating the data, makind block-mean with different block dimension

		UDAve_Vec[i]  = AveVectorUD(rnd,N*L[i],N);
		ExpAve_Vec[i] = AveVectorExp(rnd,N*L[i],N,lambda);
		CLAve_Vec[i]  = AveVectorCL(rnd,N*L[i],N,gamma,mean);	

	}

	std::ofstream f("output_UD_1.2.out");						//printig the data on files
	std::ofstream g("output_Exp_1.2.out");
	std::ofstream h("output_CL_1.2.out");

	f << N << std::endl;
	g << N << std::endl;
	h << N << std::endl;


	for(int i=0; i<N; ++i) {

		for(int j=0; j<dim; ++j) {

			f << UDAve_Vec[j][i]  << " ";
			g << ExpAve_Vec[j][i] << " ";
			h << CLAve_Vec[j][i]  << " ";

		}

		f << std::endl;
		g << std::endl;
		h << std::endl;

	}

	f.close();
	g.close();
	h.close();

}