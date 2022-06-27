#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include "random.h"

int main(int argc, char* argv[]) {

    Random rnd;
    rnd.Init();

    std::ofstream out("circle.out");

    int N;

    if(argc >= 2) N = std::stoi(argv[1]);
    else {

        std::cout << "Insert the number of point to generate: ";
        std::cin >> N;
    }

    for(int i=0; i<N; ++i) {
        double theta = rnd.Rannyu(0,2*M_PI);
        out << i+1 << " " << std::cos(theta) << " " << std::sin(theta);
        if(i!=(N-1)) out << std::endl;
    }

    out.close();
    
    return 0;
}