#ifndef __CITY__
#define __CITY__

#include <fstream>
#include <iostream>
#include "Coordinates.h"

class City {

    public:

    City();
    City(unsigned int label);
    ~City();

    friend void operator>>(std::istream& is, City &c); 

    void SetLabel(unsigned int l);
    void SetName(std::string name);
    void SetState(std::string state);

    unsigned int& GetLabel();
    Coordinates& GetCoords();
    
    private:

    unsigned int m_label;
    Coordinates m_coordinates;

};

double Distance( City c1, City c2 );
bool operator==(City a, City b);

#endif 