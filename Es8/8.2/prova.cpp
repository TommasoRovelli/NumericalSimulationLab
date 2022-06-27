#include "integral.h"
#include "random.h"
#include <functional>
#include <cmath>  
#include <iostream>
#include <fstream>
#include <algorithm>

double E ( std::vector<double> v) {

    // v[0] = x
    // v[1] = mu
    // v[2] = sigma

    double s1 = std::pow( (v[0]-v[1])/v[2],2);
    double s2 = std::pow( (v[0]+v[1])/v[2],2);

    double e1 = std::exp( - s1/2 );
    double e2 = std::exp( - s2/2 );

    //double pot = std::pow(v[0],4) - 5./2. * std::pow(v[0],2);
    double pot = 0.5 * std::pow(v[0],2);

    return -1/(2*std::pow(v[2],2)) * ( s1*e1 + s2*e2 - e1 - e2 ) / ( e1 + e2 ) + pot;

}

double rho ( std::vector<double> v) {

    double s1 = std::pow( (v[0]-v[1])/v[2],2);
    double s2 = std::pow( (v[0]+v[1])/v[2],2);

    double e1 = std::exp( - s1/2 );
    double e2 = std::exp( - s2/2 );

    return  std::pow( e1+e2 ,2);

}

int main(int argc, char* argv[]) {

    Random rnd;
    rnd.Init();

    Integral prova(E);

    std::vector<double> x = {0,-6.53114 ,0.102222};

    double I = 0;
    
    for(int i=0; i<100; ++i) I += prova.EvalByMetro(rho,rnd, 1000, 50, 2, x );

    std::cout << I/100 << std::endl;

    return 0;

}