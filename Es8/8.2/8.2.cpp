//Numerical Simulation Exercise
//Exercise 8.2 
//Made by Tommaso Rovelli

#include "integral.h"
#include "random.h"
#include <functional>
#include <cmath>  
#include <iostream>
#include <fstream>
#include <algorithm>

const double d_sigma=1, d_mu=1;
double beta = 0.5;

const double  d_x=1;
const double beta_max=50;
const double N=5000, eq_step=10;
const int N_blocks_per_temp = 50;
const int step_per_temp=1000;
int L = (double)step_per_temp/(double)N_blocks_per_temp;

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

    std::ofstream output_I("I.out");
    std::ofstream output_s("s.out");
    std::ofstream output_m("m.out");

    std::vector<double> dependancies(3);

    dependancies[0] = 0; //x_0
    dependancies[1] = 1; //mu
    dependancies[2] = 1; //sigma

    Integral E_av(E);

    double I_old = E_av.EvalByMetro( rho, rnd, N,  eq_step, d_x, dependancies);

    while( beta <= beta_max ) {

        double ave_I=0;
        double ave_I2=0;
        double ave_s=0;
        double ave_s2=0;
        double ave_m=0;
        double ave_m2=0;

        for( int j=0; j<N_blocks_per_temp; ++j ) {

            double sum_I=0;
            double sum_s=0;
            double sum_m=0;

            for(int i=0;i<L;++i ) {

                double old_mu=dependancies[1], old_sigma=dependancies[2];

                dependancies[1] =  rnd.Rannyu(dependancies[1]-d_mu/std::pow(beta,0.25), dependancies[1]+d_mu/std::pow(beta,0.25) );
                if(dependancies[1]<0) dependancies[1]*=-1;
                dependancies[2] = rnd.Rannyu( dependancies[2]-d_sigma/std::pow(beta,0.25) , dependancies[2]+d_sigma/std::pow(beta,0.25) );
                if(dependancies[2] < 0.2 ) dependancies[2] += 2*(0.2 - dependancies[2]); 

                double I_new = E_av.EvalByMetro( rho, rnd, N,  eq_step, d_x, dependancies);

                double p = std::exp ( - beta * (I_new-I_old));

                if( I_new < I_old )  I_old = I_new;
                else if(rnd.Rannyu() < p) I_old = I_new;
                else {
                    dependancies[2] = old_sigma;
                    dependancies[1] = old_mu;           
                }

                sum_I  += I_old;
                sum_m  += dependancies[1];
                sum_s  += dependancies[2];

            }

            ave_I += sum_I/L;
            ave_I2 += sum_I/L * sum_I/L;
            ave_m += sum_m/L;
            ave_m2 += sum_m/L * sum_m/L;
            ave_s += sum_s/L;
            ave_s2 += sum_s/L * sum_s/L;

        }

        output_I << beta << "  " << ave_I/N_blocks_per_temp << "  " << std::sqrt((ave_I2/N_blocks_per_temp - std::pow(ave_I/N_blocks_per_temp,2))/(N_blocks_per_temp-1)) << std::endl;
        output_m << beta << "  " << ave_m/N_blocks_per_temp << "  " << std::sqrt((ave_m2/N_blocks_per_temp - std::pow(ave_m/N_blocks_per_temp,2))/(N_blocks_per_temp-1)) << std::endl;
        output_s << beta << "  " << ave_s/N_blocks_per_temp << "  " << std::sqrt((ave_s2/N_blocks_per_temp - std::pow(ave_s/N_blocks_per_temp,2))/(N_blocks_per_temp-1)) << std::endl;


        std::cout << 1/beta << std::endl;

        beta += 1;

    }

    output_I.close();
    output_s.close();
    output_m.close();

    return 0;

}