#include "Path.h"
#include <vector>
#include <iterator>
#include <algorithm>

Path::Path(): m_path() {}

Path::Path(std::vector<City> v) {
    m_path=v;
}

Path::~Path() {}

std::vector<City>& Path::GetPath() { return m_path;}

void Path::SetPath(std::vector<City> v) {m_path = v;}

double Path::Measure() {

    double sum=0;

    for( int i=0; i < static_cast<int>(m_path.size()-1); ++i) sum += Distance( m_path[i], m_path[i+1]);

    sum += Distance( m_path[static_cast<int>(m_path.size())-1], m_path[0] );

    return sum;

}

void Path::Swap(unsigned int i1, unsigned int i2) {

    City tmp = m_path[i1];
    m_path[i1]=m_path[i2];
    m_path[i2]=tmp;

} 

void Path::Shift(unsigned int shift, unsigned int first, unsigned int last) {

    std::vector<City>::iterator it_1 = m_path.begin() + first;
    std::vector<City>::iterator it_2 = m_path.begin() + last+1; //+1 because the range costructor copy [first,last)
    std::vector<City>::iterator it_3 = m_path.begin() + last + shift +1;

    std::vector<City> unchanged1(m_path.begin(), it_1 );    // unchanged part of the array from start to the element precedent to the first
    std::vector<City> first_part(it_1, it_2);               // first part to be shifted
    std::vector<City> second_part(it_2,it_3);               // part that replace the shifted one
    std::vector<City> unchanged2(it_3, m_path.end());       

    m_path.clear();

    m_path.insert(m_path.end(),unchanged1.begin(),unchanged1.end());
    m_path.insert(m_path.end(),second_part.begin(),second_part.end());
    m_path.insert(m_path.end(),first_part.begin(),first_part.end());
    m_path.insert(m_path.end(),unchanged2.begin(),unchanged2.end());

}

void Path::Rotate(unsigned int first, unsigned int last, unsigned int r) {

    std::vector<City>::iterator it_1 = m_path.begin() + first;
    std::vector<City>::iterator it_2 = m_path.begin() + last + 1;
    std::vector<City>::iterator it_3 = m_path.begin() + r;

    std::rotate(it_1, it_3, it_2);

}

void Path::Reverse(unsigned int first, unsigned int last) {

    std::vector<City>::iterator it_1 = m_path.begin() + first;
    std::vector<City>::iterator it_2 = m_path.begin() + last + 1;

    std::reverse(it_1,it_2);

}
