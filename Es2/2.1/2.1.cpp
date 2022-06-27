//Numerical Simulation Laboratory
//Exercise 2.1
//Made by Tommaso Rovelli 944280

#include <fstream>
#include <cmath>
#include "func.h"
#include "random.h"
#include "integral.h"

double My_Function( double x) {																//function I have to integrate

	return M_PI/2 * std::cos(M_PI * x /2);
}

double My_Distrib( double x) {																//distribution I chose for Important Sampling

	return 2*(1-x);
}

double My_Inverse( double x) {																//inverse of my distibution

	return 1 - std::sqrt(1-x);

}

double UD_Distrib (double x) { return 1; }													//uniform distribution for Mean Method

int main(int argc, char* argv[]) {

	Random rnd;
	rnd.Init();

	int L = 100;																			//number of values per block
	int N = 100;																			//number of blocks 

	int n_points = 1000;

	double upper_bound = 1;																	//integral bounds
	double lower_bound = 0;

	Integral my_integral(My_Function, lower_bound, upper_bound);

	std::vector<double> IS_integration(N);
	std::vector<double> UD_integration(N);

	double IS_sum, UD_sum;

	for(int i=0; i<N; ++i) {																//blocking

		IS_sum=0;
		UD_sum=0;

		for(int j=0; j<L; ++j) {

			IS_sum += my_integral.EvalByIS_inv(My_Inverse, My_Distrib, rnd, n_points);		//EvalByIS_inv evals the integral using the inverse method to compute the distribution
			UD_sum += my_integral.EvalByIS_rej(UD_Distrib, 1, rnd, n_points);				//EvalByIs_rej evals the integral using the accept-reject method to compute the distribution

		}

		IS_integration[i] = IS_sum/L;
		UD_integration[i] = UD_sum/L;
	}

	std::vector<double> IS_ave(CumulativeAve(IS_integration));
	std::vector<double> UD_ave(CumulativeAve(UD_integration));

	std::vector<double> IS_err(Error(IS_integration));
	std::vector<double> UD_err(Error(UD_integration));

	std::ofstream f("output_IS_2.1.out");													//printing the data on files
	std::ofstream g("output_UD_2.1.out");

	f << N << " " << L << std::endl;
	g << N << " " << L << std::endl;

	for(int i=0;i<N;++i) {

		f << IS_ave[i] << " " << IS_err[i] << std::endl;
		g << UD_ave[i] << " " << UD_err[i] << std::endl;

	}

	f.close();
	g.close();

	return 0;

}
