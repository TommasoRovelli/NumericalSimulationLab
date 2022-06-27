//Made by Tommaso Rovelli

#include "blackscholes.h"
#include <cmath>

BlackScholes::BlackScholes() {}

BlackScholes::BlackScholes(double S_0, double T, double K, double r, double sigma) {

	m_S_0 = S_0;
	m_T = T;
	m_K = K;
	m_r = r;
	m_sigma = sigma;

}

BlackScholes::~BlackScholes() {}

void BlackScholes::SetS_0(double S_0) { m_S_0 = S_0; }
void BlackScholes::SetT(double T) { m_T = T; }
void BlackScholes::SetK(double K) { m_K = K; }
void BlackScholes::SetR(double R) { m_r = R; }
void BlackScholes::SetSigma(double sigma) { m_sigma = sigma; }

std::vector<double> BlackScholes::Call(Random &rnd, int M) {

	std::vector<double> call(M);

	for(int i=0; i<M; ++i) {

		double S_T = m_S_0 * std::exp( (m_r-0.5*std::pow(m_sigma,2)*m_T + m_sigma*rnd.Gauss(0,m_T) ) );
		
		if( S_T-m_K > 0) call[i] = std::exp( -m_r*m_T ) * (S_T-m_K);
		else call[i] = 0;

	}

	return call;

}

std::vector<double> BlackScholes::Put(Random &rnd, int M) {

	std::vector<double> put(M);

	for(int i=0; i<M; ++i) {

		double S_T = m_S_0 * std::exp( (m_r-0.5*std::pow(m_sigma,2)*m_T + m_sigma*rnd.Gauss(0,m_T) ) );
		
		if( m_K-S_T > 0) put[i] = std::exp( -m_r*m_T ) * (m_K-S_T);
		else put[i] = 0;

	}

	return put;

}

std::vector<double> BlackScholes::Call(Random &rnd, int M, int n_steps) {

	std::vector<double> call(M);

	double d_t = m_T/n_steps;
	double S = 0;

	for(int i=0; i<M ; ++i) {

		S = m_S_0;

		for(int j=0; j<n_steps; ++j) {

			S = S * std::exp( (m_r-0.5*std::pow(m_sigma,2))*d_t + m_sigma*rnd.Gauss(0,1)*std::sqrt(d_t) );

		}

		if( S-m_K > 0) call[i] = std::exp( -m_r*m_T ) * (S-m_K);
		else call[i] = 0;

	}

	return call;

}

std::vector<double> BlackScholes::Put(Random &rnd, int M, int n_steps) {

	std::vector<double> put(M);

	double d_t = m_T/n_steps;
	double S =0;

	for(int i=0; i<M ; ++i) {

		double S_pre = m_S_0;

		for(int j=0; j<n_steps; ++j) {

			S = S_pre * std::exp( (m_r-0.5*std::pow(m_sigma,2))*d_t + m_sigma*rnd.Gauss(0,1)*std::sqrt(d_t) );
			S_pre = S;


		}

		if( m_K-S > 0) put[i] = std::exp( -m_r*m_T ) * (m_K-S);
		else put[i] = 0;

	}

	return put;

}