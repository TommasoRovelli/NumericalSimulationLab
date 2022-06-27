//Made by Tommaso Rovelli 944280

#ifndef __RandomWalk__
#define __RandomWalk__

#include <vector>
#include "random.h"

class RandomWalk {

public:

	RandomWalk();
	RandomWalk(double a);
	RandomWalk(int dim);
	RandomWalk(double a, int dim);

	void SetA(double a);
	void SetDim(int dim);

	const std::vector<double>& GetPosition();
	const std::vector<std::vector<double>>& GetHistory();

	std::vector<double> GetDistanceHistory();

	void LatticeStep( Random &rnd);
	void Continuum3DStep( Random &rnd);

	void Restart();


private:

	double m_a;
	int m_dim;
	std::vector<double> m_position;
	std::vector<std::vector<double>> m_history;

};

#endif