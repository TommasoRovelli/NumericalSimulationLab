//Made by Tommaso Rovelli 944280

#include "func.h"


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

std::vector<double> AveVectorUD(Random &rndm, int M, int N) {

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







