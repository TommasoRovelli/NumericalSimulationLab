//Made by Tommaso Rovelli 944280

#ifndef __Integral__
#define __Integral__

#include <functional>
#include "random.h"

class Integral {

public:

	Integral();
	Integral(std::function<double(double)> f);
	Integral(std::function<double(double)> f, double a, double b);

	~Integral();

	void SetFunction(std::function<double(double)> f);
	void SetA(double a);
	void SetB(double b);

	double EvalByIS_rej(std::function<double(double)> my_distrib, double max, Random &rnd, int N);
	double EvalByIS_inv(std::function<double(double)> my_inverse, std::function<double(double)> my_distrib, Random &rnd, int N);


private:

	std::function<double(double)> m_f;
	double m_a,m_b;

};

#endif