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

    std::ofstream out("square.out");

    int N;

    if(argc >= 2) N = std::stoi(argv[1]);
    else {

        std::cout << "Insert the number of point to generate: ";
        std::cin >> N;

    }

    for(int i=0; i<N; ++i) {
        double x = rnd.Rannyu(0,1);
        double y = rnd.Rannyu(0,1);
        out << i+1 << " " << x << " " << y;
        if(i!=(N-1)) out << std::endl;
    }

    out.close();
    
    return 0;
}