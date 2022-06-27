#ifndef __COORDINATES__
#define __COORDINATES__

#include <cmath>
#include <fstream>
#include <iostream>

class Coordinates {

    public:

    Coordinates();
    Coordinates(double x, double y);
    ~Coordinates();
    
    void SetX(double x);
    void SetY(double y);

    double& GetX();
    double& GetY();

    private:

    double m_x;
    double m_y;
};


#endif