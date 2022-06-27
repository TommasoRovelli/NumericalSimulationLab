#include "City.h"
#include <fstream>
#include <cmath>
#include <iostream>
#include "Coordinates.h"

City::City(): m_coordinates() {
    m_label=0;
}
City::~City() {}

City::City(unsigned int label) {m_label=label;}

void City::SetLabel(unsigned int l) {m_label=l;}

unsigned int& City::GetLabel() {return m_label;}
Coordinates& City::GetCoords() {return m_coordinates;}

double Distance(City c1, City c2) { return std::sqrt(std::pow( c1.GetCoords().GetX() - c2.GetCoords().GetX(),2) + std::pow( c1.GetCoords().GetY() - c2.GetCoords().GetY(),2)); }

void operator>>(std::istream& is, City &c) {

    std::string name, state;
    double label,x,y;

    is >> label >> x >> y >> state >> name;

    c.SetLabel(label);
    c.GetCoords().SetX(x);
    c.GetCoords().SetY(y);

}

bool operator==(City a, City b) {

    if( a.GetLabel() == b.GetLabel() ) return true;
    else return false;

}