//Made by Tommaso Rovelli 944280

#ifndef __Buffon__
#define __Buffon__

#include "random.h"
#include <vector>

class Buffon {

public:

	Buffon();
	Buffon(double L, double d);
	~Buffon();

	void SetLength(double L);
	void SetDistance(double d);

	bool Throw(Random &rnd);

	std::vector<double> PiExtimationVector(int len, int throws,  Random &rnd);
	
private:

	double m_L, m_d;

};

#endif