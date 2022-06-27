//Made by Tommaso Rovelli 944280

#ifndef __BlackScholes__
#define __BlackScholes__

#include <vector>
#include "random.h"

class BlackScholes {

public:

	BlackScholes();
	BlackScholes(double S_0, double T, double K, double r, double sigma);

	~BlackScholes();

	void SetS_0(double S_0);
	void SetT(double T);
	void SetK(double K);
	void SetR(double r);
	void SetSigma(double sigma);

	std::vector<double> Call(Random &rnd, int M);
	std::vector<double> Call(Random & rnd, int M, int n_step);

	std::vector<double> Put(Random &rnd, int M);
	std::vector<double> Put(Random &rnd, int M, int n_step);

private:

	double m_S_0;
	double m_T;
	double m_K;
	double m_r;
	double m_sigma;

};

#endif 