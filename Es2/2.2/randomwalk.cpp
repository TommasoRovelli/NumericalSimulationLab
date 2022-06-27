//Made by Tommaso Rovelli 944280

#include "randomwalk.h"
#include "random.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>

RandomWalk::RandomWalk() { 

	m_dim = 3; //default 3D
	std::vector<double> v(m_dim);
	m_position = v;

}

RandomWalk::RandomWalk(double a) { 

	m_a=a;
	m_dim = 3; //default 3D
	std::vector<double> v(m_dim);
	m_position = v;

}

RandomWalk::RandomWalk(int dim) {

	m_dim = dim;
	std::vector<double> v(m_dim);
	m_position = v;

}

RandomWalk::RandomWalk(double a, int dim) {

	m_a=a;
	m_dim = dim;
	std::vector<double> v(m_dim);
	m_position = v;

}

void RandomWalk::SetA( double a) { m_a=a;}

void RandomWalk::SetDim( int dim) { m_dim=dim;}

void RandomWalk::LatticeStep(Random &rnd) {

	int index = static_cast<int>(rnd.Rannyu(0,m_dim));

	if( rnd.Rannyu()>=0.5) m_position[ index] += m_a;
	else m_position[ index ] -= m_a;

	m_history.push_back(m_position);
}

void RandomWalk::Continuum3DStep(Random &rnd) {

	if(m_dim != 3 ) {
		std::cout << "The dimension of the Random Walk is not 3, the continuum step is implemented only for a 3D RW" << std::endl;
		exit(0);
	}

	double cos_theta = rnd.Rannyu(1,-1);
	double sin_theta = std::sqrt( 1 - std::pow(cos_theta,2));
	double phi = rnd.Rannyu(0,2*M_PI);

	m_position[0] += m_a * sin_theta * std::cos(phi);
	m_position[1] += m_a * sin_theta * std::sin(phi);
	m_position[2] += m_a * cos_theta;

	m_history.push_back(m_position);
	
}

void RandomWalk::Restart() { 

	std::vector<double> v(m_dim);
	m_position = v;
	m_history.clear();
	
}

const std::vector<double>& RandomWalk::GetPosition() { return m_position;}

const std::vector<std::vector<double>>& RandomWalk::GetHistory() { return m_history;}

std::vector<double> RandomWalk::GetDistanceHistory() {

	int size = m_history.size();

	std::vector<double> distance(size);

	for(int i=0;i<size;++i) {

		for(int j=0; j<m_dim; ++j) distance[i] += std::pow( m_history[i][j], 2);

		distance[i] = std::sqrt(distance[i]);
	}

	return distance;

}
