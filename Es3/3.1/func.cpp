//Made by Tommaso Rovelli 944280

#include "func.h"
#include <iostream>
#include <stdlib.h>

void operator+=(std::vector<double> &x, std::vector<double> y) {

	int dim1 = x.size();
	int dim2 = y.size();

	if( dim2 != dim1) {

		std::cout << "Trying to sum two vector with different size, non possible" << std::endl;
		exit(0);
	}

	for(int i=0; i< dim1; ++i) x[i] +=y[i]; 

}

std::vector<double> operator/(std::vector<double> v,double den) {

	int dim = v.size();

	std::vector<double> vec(dim);

	for(int i=0; i<dim; ++i) vec[i] = v[i]/den;

	return vec;

}

std::vector<double> operator^(std::vector<double> v, double exp) {

	int dim = v.size();

	std::vector<double> vec(dim);

	for(int i=0; i<dim; ++i) vec[i] = std::pow(v[i],exp);

	return vec;

}

std::vector<double> operator+(std::vector<double> x, std::vector<double> y) {

	int dim1 = x.size();
	int dim2 = y.size();

	if( dim2 != dim1) {

		std::cout << "Trying to sum two vector with different size, non possible" << std::endl;
		exit(0);
	}

	std::vector<double> sum(dim1);

	for(int i=0; i< dim1; ++i) {

		sum[i] = x[i] + y[i];
	}


	return sum;
}

std::vector<double> operator-(std::vector<double> x, std::vector<double> y) {

	int dim1 = x.size();
	int dim2 = y.size();

	if( dim2 != dim1) {

		std::cout << "Trying to sottract two vector with different size, non possible" << std::endl;
		exit(0);
	}

	std::vector<double> difference(dim1);

	for(int i=0; i< dim1; ++i) difference[i] = x[i] - y[i];

	return difference;
}


std::vector<double> SquaredVector(std::vector<double> vec) {

	int N = vec.size();
	std::vector<double> SquaredVector(N);

	for(int i=0;i<N;++i) SquaredVector[i] = std::pow(vec[i],2);

	return SquaredVector;
}

std::vector<double> CumulativeAve (std::vector<double> vec) {

	int N = vec.size();
	std::vector<double> cumulAve(N);

	for(int i=0;i<N;++i) {

		for(int j=0;j<=i;++j) cumulAve[i] += vec[j];

		cumulAve[i] = cumulAve[i]/(i+1);
	}

	return cumulAve;

}

std::vector<double> Error(std::vector<double> vec) {

	int N = vec.size();

	std::vector<double> CumAve(CumulativeAve(vec));
	std::vector<double> CumSqrdAve(CumulativeAve(SquaredVector(vec)));
	std::vector<double> err(N);

	err[0] = 0;
	for(int i=1;i<N;++i) err[i] = std::sqrt( (CumSqrdAve[i] - std::pow(CumAve[i],2))/i );

	return err;

}

std::vector<double> Blocks(std::vector<double> vec, int n_blocks) {

	double L = static_cast<int>(vec.size()/n_blocks);

	std::vector<double> blocks(n_blocks);

	for( int i=0; i<n_blocks; ++i) {

		double sum = 0;

		for(int j=0;j<L;++j) {

			int k = j + i*L;
			sum += vec[k];
		}

		blocks[i] = sum/L;

	}

	return blocks;

}

std::vector<double> AveVectorUD(Random &rndm, int M, int N) {

	rndm.Init();

	int L = static_cast<int>(M/N);

	std::vector<double> rndmAll(M);
	std::vector<double> AveBlock(N);

	for(int i=0;i<M;++i) rndmAll[i] = rndm.Rannyu();

	for(int i=0;i<N;++i) {

		double sum = 0;
		
		for(int j=0;j<L;++j) {

			int k = j + i*L;
			sum += rndmAll[k];
		}

		AveBlock[i] = sum/L;

	}

	return AveBlock;

}

std::vector<double> AveVectorExp(Random &rndm, int M, int N, double lambda) {

	rndm.Init();

	int L = static_cast<int>(M/N);

	std::vector<double> rndmAll(M);
	std::vector<double> AveBlock(N);

	for(int i=0;i<M;++i) rndmAll[i] = rndm.Exp(lambda);

	for(int i=0;i<N;++i) {

		double sum = 0;
		
		for(int j=0;j<L;++j) {

			int k = j + i*L;
			sum += rndmAll[k];
		}

		AveBlock[i] = sum/L;

	}

	return AveBlock;

}

std::vector<double> AveVectorCL(Random &rndm, int M, int N, double gamma, double mean) {

	rndm.Init();

	int L = static_cast<int>(M/N);

	std::vector<double> rndmAll(M);
	std::vector<double> AveBlock(N);

	for(int i=0;i<M;++i) rndmAll[i] = rndm.CauchyLorentz(gamma, mean);

	for(int i=0;i<N;++i) {

		double sum = 0;
		
		for(int j=0;j<L;++j) {

			int k = j + i*L;
			sum += rndmAll[k];
		}

		AveBlock[i] = sum/L;

	}

	return AveBlock;

}


std::vector<double> StdvVectorUD(Random &rndm, int M, int N, double theoric_mean) {

	int L = static_cast<int>(M/N);

	std::vector<double> rndmStdvAll(M);
	std::vector<double> StdvBlock(N);

	for(int i=0;i<M;++i) rndmStdvAll[i] = std::pow( rndm.Rannyu() - theoric_mean, 2);

	for(int i=0;i<N;++i) {

		double sum = 0;

		for(int j=0;j<L;++j) {

			int k = j + i*L;
			sum += rndmStdvAll[k];
		}

		StdvBlock[i] = sum/L; 

	}

	return StdvBlock;

}


std::vector<double> ChiSquared(Random &rnd, int N_bins, int N_throws, int N_times) {

	std::vector<double> chi_squared(N_times);

	double expected_value = static_cast<double>(N_throws/N_bins);

	for(int i=0;i<N_times;++i) {

		std::vector<double> throws_count(N_bins);
		double sum = 0;

		for(int j=0;j<N_throws;++j) throws_count[static_cast<int>(rnd.Rannyu()*N_bins)]++;

		for(int j=0;j<N_bins;++j) sum += std::pow( throws_count[j]-expected_value,2); 

		chi_squared[i] = sum / expected_value;
	}

	return chi_squared;
 
}







