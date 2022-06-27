//Made by Tommaso Rovelli 944280

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"
#include "integral.h"

Integral::Integral() {};

Integral::Integral(std::function<double(double)> f) { m_f = f; }


Integral::Integral(std::function<double(double)> f, double a, double b) {

	m_f = f;
	m_a = a;
	m_b = b;

}

Integral::~Integral() {};

void Integral::SetFunction( std::function<double(double)> f) { m_f = f; }

void Integral::SetA( double a) { m_a = a; }

void Integral::SetB( double b) { m_b = b; }

double Integral::EvalByIS_rej(std::function<double(double)> my_distrib, double max, Random &rnd, int N) {

	double x = rnd.MyDistribReject(my_distrib, m_a, m_b, max);
	double sum=0;

	for(int i=0; i<N; ++i) sum += (m_f(x)/my_distrib(x));

	sum = sum/N;

	return sum;

}

double Integral::EvalByIS_inv(std::function<double(double)> my_inverse, std::function<double(double)> my_distrib, Random &rnd, int N) {

	double x = rnd.MyDistribInverse(my_inverse);
	double sum=0;

	for(int i=0; i<N; ++i) sum += (m_f(x)/my_distrib(x));

	sum = sum/N;

	return sum;

}

