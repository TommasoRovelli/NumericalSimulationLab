//Made by Tommaso Rovelli 944280

#include "buffon.h"
#include "random.h"
#include <cmath>
#include <numeric>

Buffon::Buffon() {};

Buffon::Buffon(double L, double d) {

	m_L=L;
	m_d=d;

}

Buffon::~Buffon() {};

void Buffon::SetLength(double L) {m_L = L;}

void Buffon::SetDistance(double d) {m_d = d;}

bool Buffon::Throw(Random &rnd) {

	double x = rnd.Rannyu(0,m_d);

	double Rcos_t, Rsen_t, R;
	bool in = false;

	while(!in) {

		Rcos_t = rnd.Rannyu(-1,1);
		Rsen_t = rnd.Rannyu(-1,1);

		R = std::sqrt( std::pow(Rcos_t,2) + std::pow(Rsen_t,2));

		if( R < 1) in = true;

	}

	double x_f = x + m_L * Rcos_t/R;

	if(x_f <= 0 || x_f >= m_d) return 1;

	return 0;

	//we can also use the following code
	/*

	double x = rnd.Rannyu(0,m_d);

	double x_2, y_2;
	bool in = false;


	while(!in) {
		x_2 = rnd.Rannyu(x-m_L, x+m_L);
		y_2 = rnd.Rannyu(-m_L, m_L);

		double R = std::sqrt( std::pow( x-x_2,2) + std::pow(y_2,2));

		if( R<m_L && R!=0) in = true;
	}
	
	if(x_2 <= x) {

		double y = y_2 * (-x) / (x_2-x);

		double dist = std::sqrt( std::pow( x,2) + std::pow(y,2));

		if(dist < m_L) return 1;
		else return 0;

	}

	if(x_2 > x) {

		double y = y_2 * (m_d-x) / (x_2-x);

		double dist = std::sqrt( std::pow( x-m_d,2) + std::pow(y,2));

		if(dist < m_L) return 1;
		else return 0;

	}


	*/

	return 0;
}

std::vector<double> Buffon::PiExtimationVector(int N, int throws, Random &rnd) {

	std::vector<double> PIs(N);

	for(int i=0; i<N; ++i) {

		for(int j=0; j<throws; ++j) PIs[i] += Throw(rnd);

		PIs[i] = 2*m_L*throws/(PIs[i]*m_d);
	}

	return PIs;

}
