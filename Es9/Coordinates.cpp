#include "Coordinates.h"

Coordinates::Coordinates() {
    m_x=0;
    m_y=0;
}
Coordinates::Coordinates(double x, double y) { m_x=x; m_y=y;}
Coordinates::~Coordinates() {}

void Coordinates::SetX(double x) {m_x=x;}
void Coordinates:: SetY(double y) {m_y=y;}

double& Coordinates::GetX() {return m_x;}
double& Coordinates::GetY() {return m_y;}

