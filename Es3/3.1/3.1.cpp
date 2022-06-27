//Numerical Simulation Laboratory
//Exercise 3.1
//Made by Tommaso Rovelli 944280

#include <fstream>
#include "func.h"
#include "random.h"
#include "blackscholes.h"

int main( int argc, char* argv[]) {

	Random rnd;
	rnd.Init();

	double S_0 = 100;
	double delivery_time = 1;
	double strike_price = 100;
	double r = 0.1;
	double volatility = 0.25;

	int M = 10000;
	int N = 100;

	int n_step = 100;

	BlackScholes bs(S_0, delivery_time, strike_price, r, volatility);

	std::vector<double> dir_call_blocks(Blocks(bs.Call(rnd,M),N));
	std::vector<double> step_call_blocks(Blocks(bs.Call(rnd,M,n_step),N));
	std::vector<double> dir_put_blocks(Blocks(bs.Put(rnd,M),N));
	std::vector<double> step_put_blocks(Blocks(bs.Put(rnd,M,n_step),N));

	std::vector<double> dir_call(CumulativeAve(dir_call_blocks));
	std::vector<double> err_dir_call(Error(dir_call_blocks));

	std::vector<double> step_call(CumulativeAve(step_call_blocks));
	std::vector<double> err_step_call(Error(step_call_blocks));

	std::vector<double> dir_put(CumulativeAve(dir_put_blocks));
	std::vector<double> err_dir_put(Error(dir_put_blocks));

	std::vector<double> step_put(CumulativeAve(step_put_blocks));
	std::vector<double> err_step_put(Error(step_put_blocks));

	std::ofstream f("output_dir_call_3.1.out");
	std::ofstream g("output_step_call_3.1.out");
	std::ofstream h("output_dir_put_3.1.out");
	std::ofstream i("output_step_put_3.1.out");


	f << M << " " << N << std::endl;
	g << M << " " << N << std::endl;
	h << M << " " << N << std::endl;
	i << M << " " << N << std::endl;

	for(int j=0; j<N; ++j) {

		f << dir_call[j] << " " << err_dir_call[j] << std::endl;
		g << step_call[j] << " " << err_step_call[j] << std::endl;
		h << dir_put[j] << " " << err_dir_put[j] << std::endl;
		i << step_put[j] << " " << err_step_put[j] << std::endl;

	}

	f.close();
	g.close();
	h.close();
	i.close();

	return 0;

}