#include "TravellingSalesman.h"
#include "random.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {

    std::string filename;

    int N_gen=500;
    double div= N_gen/100.;
    double mutation_prob = 0.1;
    double crossover_prob = 0.5;

    int index=1;

    std::ofstream out("output.out");
    std::ofstream out_mean("mean.out");
    std::ofstream out_best("best.out");

    Random rnd;
    rnd.Init();

    if(argc >= 2) filename = argv[1];
    else{
        std::cout<<"Insert input file:";
        std::cin >> filename;
    }

    TravellingSalesman TS(filename);
    TS.GeneratePopulation();
    
    Path best(TS.BestPath());

    out_best << best.Measure() << std::endl;

    for(int i=0; i<N_gen; ++i) {

        double mean=0;
        double mean2=0;
        unsigned int len = (unsigned int)TS.GetPopDim()/2.;

        if(i%(int)(div) == 0) std::cout << (double)i/double(div) << "%  "<< std::endl;
        
        //std::cout << i << std::endl;

        TS.Order();
        for(unsigned  int j=0; j<len; ++j) {
            mean += TS.GetPopulation()[j].Measure();
            mean2 += std::pow(TS.GetPopulation()[j].Measure(),2);
        }

        mean /= len;
        double err = std::sqrt(mean2/len - std::pow(mean,2));

        TS.Crossover(crossover_prob);

        TS.Mutation1(mutation_prob);
        TS.Mutation2(mutation_prob);
        TS.Mutation3(mutation_prob);
        TS.Mutation4(mutation_prob);

        //TS.Check();

        if( best.Measure() > TS.BestPath().Measure()) {

            std::string s = ".out";

            std::string::size_type i = filename.find(s);

            if (i != std::string::npos)
            filename.erase(i, s.length());

            std::string f_name = "Paths_" + filename + "/best" + std::to_string(index) +  ".out";
            //std::ofstream path_out(f_name);
            
            best.SetPath(TS.BestPath().GetPath());

            //for( int i=0; i<(int)best.GetPath().size(); ++i) path_out << best.GetPath()[i].GetLabel() << " " << best.GetPath()[i].GetCoords().GetX() << " " << best.GetPath()[i].GetCoords().GetY() << std::endl;
            //path_out << best.GetPath()[0].GetLabel() << " " << best.GetPath()[0].GetCoords().GetX() << " " << best.GetPath()[0].GetCoords().GetY() << std::endl;

            //path_out.close();
            ++index;
        }

        out_best << TS.BestPath().Measure() << std::endl;
        out_mean << i << " " << mean << " " << err << std::endl;

    }

    for( int i=0; i<(int)best.GetPath().size(); ++i) out << best.GetPath()[i].GetLabel() << " " << best.GetPath()[i].GetCoords().GetX() << " " << best.GetPath()[i].GetCoords().GetY() << std::endl;

    out << best.GetPath()[0].GetLabel() << " " << best.GetPath()[0].GetCoords().GetX() << " " << best.GetPath()[0].GetCoords().GetY() << std::endl;

    return 0;

}