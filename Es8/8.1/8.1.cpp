//Numerical Simulation Exercise 
//Exercise 8.1
//Made by Tommaso Rovelli

#include "integral.h"
#include "random.h"
#include <functional>
#include <cmath>  
#include <iostream>
#include <fstream>

double E ( std::vector<double> v) {

    // v[0] = x
    // v[1] = mu
    // v[2] = sigma

    double s1 = std::pow( (v[0]-v[1])/v[2],2);
    double s2 = std::pow( (v[0]+v[1])/v[2],2);

    double e1 = std::exp( - s1/2 );
    double e2 = std::exp( - s2/2 );

    double pot = std::pow(v[0],4) - 5./2. * std::pow(v[0],2);
    //double pot = 0.5 * std::pow(v[0],2);

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

    std::ofstream output("integral.out");

    int N = 5000, eq_step = 10;
    double d_x=1;

    std::vector<double> dependancies(3);

    dependancies[0]=0; //x_0
    dependancies[1]=0.799217; //mu
    dependancies[2]=0.642638; //sigma

    int N_blocks=20, L =100;

    Integral E_av(E);

    double ave=0;
    double ave2=0;

    for(int i=0; i<N_blocks; i++){

        std::cout << i << std::endl;
        
        double sum  = 0;
            
        for (int j=0; j<L; j++) sum += E_av.EvalByMetro( rho, rnd, N,  eq_step, d_x, dependancies);
        
        
        ave += sum/L;                            // r_i
        output<< i+1 << " " << ave/(i+1)<<" ";                  // printing the mean until this block
        ave2 += pow(sum/L,2);                     // (r_i)^2
        if(i==0) output<<0<<" ";
        else output<< std::sqrt((ave2/(i+1) - std::pow(ave/(i+1),2))/(i))<<" ";
            
        output<<std::endl;

    }

    return 0;

}
