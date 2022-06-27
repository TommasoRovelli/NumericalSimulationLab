#ifndef __PATH__
#define __PATH__

#include "City.h"
#include <vector>

class Path {

    public:

    Path();
    Path(std::vector<City> v);
    ~Path();

    void SetPath(std::vector<City> v);
    std::vector<City>& GetPath();

    double Measure();
    void Swap(unsigned int i1, unsigned int i2);
    void Shift(unsigned int shift, unsigned int first, unsigned int last);
    void Reverse(unsigned int first, unsigned int last);
    void Rotate(unsigned int first, unsigned int last, unsigned int r);

    private:

    std::vector<City> m_path;

};


#endif