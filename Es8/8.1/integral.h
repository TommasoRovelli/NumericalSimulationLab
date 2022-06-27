//Made by Tommaso Rovelli 944280

#ifndef __Integral__
#define __Integral__

#include <functional>
#include "random.h"
#include <vector>

class Integral {

public:

	Integral();
	Integral(std::function<double(std::vector<double>)> f);
	Integral(std::function<double(std::vector<double>)> f, double a, double b);

	~Integral();

	void SetFunction(std::function<double(std::vector<double>)> f);
	void SetA(double a);
	void SetB(double b);

	//double EvalByIS_rej(std::function<double(double)> my_distrib, double max, Random &rnd, int N);
	//double EvalByIS_inv(std::function<double(double)> my_inverse, std::function<double(double)> my_distrib, Random &rnd, int N);
	double EvalByMetro(std::function<double(std::vector<double>)> my_distrib, Random &rnd, int N, int eq_step, double d, std::vector<double> dep);


private:

	std::function<double(std::vector<double>)> m_f;
	double m_a,m_b;

};

#endif