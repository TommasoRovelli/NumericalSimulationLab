/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"

using namespace std;

Random :: Random(){}

Random :: ~Random(){}

void Random :: Init() {

   int seed[4];
      int p1, p2;

      std::ifstream Primes("Primes");

      if (Primes.is_open()){
        Primes >> p1 >> p2 ;
      } else std::cerr << "PROBLEM: Unable to open Primes" << std::endl;

      Primes.close();

      std::ifstream input("seed.in");
      std::string property;
      if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
         input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            SetRandom(seed,p1,p2);
            }
         }
         input.close();
      } else std::cerr << "PROBLEM: Unable to open seed.in" << std::endl;

}

void Random :: Init(int line) {

   int seed[4];
      int p1, p2;

      std::ifstream Primes("Primes");

      if (Primes.is_open()){
         for(int i=0;i<line+1;++i) Primes >> p1 >> p2 ;
      } else std::cerr << "PROBLEM: Unable to open Primes" << std::endl;

      Primes.close();

      std::ifstream input("seed.in");
      std::string property;
      if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
         input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            SetRandom(seed,p1,p2);
            }
         }
         input.close();
      } else std::cerr << "PROBLEM: Unable to open seed.in" << std::endl;

}

void Random :: SaveSeed(){
   ofstream WriteSeed;
   WriteSeed.open("seed.out");
   if (WriteSeed.is_open()){
      WriteSeed << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
   } else cerr << "PROBLEM: Unable to open random.out" << endl;
  WriteSeed.close();
  return;
}

double Random :: Gauss(double mean, double sigma) {
   double s=Rannyu();
   double t=Rannyu();
   double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
   return mean + x * sigma;
}

int Random::RndInt(int max) {
   return static_cast<int>(Rannyu(0, max));
}

double Random :: Rannyu(double min, double max){
   return min+(max-min)*Rannyu();
}

double Random :: Rannyu(void){
  const double twom12=0.000244140625;
  int i1,i2,i3,i4;
  double r;

  i1 = l1*m4 + l2*m3 + l3*m2 + l4*m1 + n1;
  i2 = l2*m4 + l3*m3 + l4*m2 + n2;
  i3 = l3*m4 + l4*m3 + n3;
  i4 = l4*m4 + n4;
  l4 = i4%4096;
  i3 = i3 + i4/4096;
  l3 = i3%4096;
  i2 = i2 + i3/4096;
  l2 = i2%4096;
  l1 = (i1 + i2/4096)%4096;
  r=twom12*(l1+twom12*(l2+twom12*(l3+twom12*(l4))));

  return r;
}

void Random :: SetRandom(int * s, int p1, int p2){
  m1 = 502;
  m2 = 1521;
  m3 = 4071;
  m4 = 2107;
  l1 = s[0];
  l2 = s[1];
  l3 = s[2];
  l4 = s[3];
  n1 = 0;
  n2 = 0;
  n3 = p1;
  n4 = p2;

  return;
}

double Random :: Exp(double lambda) {

   return -(1/lambda * std::log(1-Rannyu()));

}

double Random :: CauchyLorentz(double gamma, double mean) {

   return gamma*std::tan(M_PI*(Rannyu()-.5)) + mean;

}

double Random :: MyDistribReject(std::function<double(double)> f,double a, double b, double Max) {

   double x,y;

   bool extracted = false;

   while(!extracted) {

      x = Rannyu(a,b);
      y = Rannyu(0,Max);

      if(y <= f(x)) extracted = true;
   }

   return x;

}

double Random :: MyDistribInverse(std::function<double(double)> f) {

   double y = Rannyu();
   double x = f(y);

   return x;

}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/