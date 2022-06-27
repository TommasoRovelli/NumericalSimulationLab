//Numerical Simulation Laboratory
//Exercise 1.1
//Made by Tommaso Rovelli 944280

#include <fstream> 
#include "func.h"

int main(int argc, char* argv[]) {

	Random rnd;	

	int M = 100000;        														//number of throws
	int N = 100;	      														//number of data per block
	double t_meanUD = .5;														//mean of the uniform distribution 

	int N_bins = 100;     														//number of intervals for the computing of chi^2
	int N_throws = 10000; 														//numbers of throws for the comuting of chi^2
	int N_times = 1000;   														//number of times I generate N_throws data for the computing of chi^2

	rnd.Init();                                    								//initializing of the Random object 
	std::vector<double> ave(AveVectorUD(rnd,M,N));  							//creating a vector of M uniform distribuited elements, the array is already in blocks form
	
	rnd.Init();												   					//reinizialization of the Random object to have the same graph of my friends
	std::vector<double> stdv(StdvVectorUD(rnd,M,N,t_meanUD));  					//creating a vector of standar deviation of an uniform distribuited set of elements, the array is already in blocks form

	rnd.Init();
	std::vector<double> chi_squared(ChiSquared(rnd,N_bins,N_throws,N_times));   //array of the value of the chi^2 for each interval

	std::vector<double> cumulative_ave(CumulativeAve(ave));						//vector of comulative mean of the means of the UD
	std::vector<double> cumulative_stdv(CumulativeAve(stdv));					//vector of comulative mean of the std dev of the UD

	std::vector<double> err_ave(Error(ave));									//vector of cumulative errors of the mean of the UD
	std::vector<double> err_stdv(Error(stdv));									//vector of cumulative errors of the std dev of the UD

	std::ofstream f("output_ave_1.1.out");										//printig the data on files
	std::ofstream g("output_stdv_1.1.out");
	std::ofstream h("output_chisqrd_1.1.out");

	f << M << " " << N << std::endl;
	g << M << " " << N << std::endl;

	for(int i=0;i<N;++i) {
		f << cumulative_ave[i]  << " " << err_ave[i]  << std::endl;
		g << cumulative_stdv[i] << " " << err_stdv[i] << std::endl;
	}

	for(int i=0;i<N_times;++i) {

		h << chi_squared[i] << std::endl;

	}

	f.close();
	g.close();
	h.close();

	return 0;

}
