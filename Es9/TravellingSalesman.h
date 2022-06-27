#ifndef __TRAVELLINGSALESMAN__
#define __TRAVELLINGSALESMAN__

#include <fstream>
#include <string>
#include <vector>
#include "City.h"
#include "Path.h"
#include "random.h"

class TravellingSalesman {

    public:

    TravellingSalesman(const std::string &filename);
    ~TravellingSalesman();

    std::vector<Path>& GetPopulation();

    Path BestPath();
    void GeneratePopulation();

    unsigned int& GetPopDim();

    void Order();

    void Mutation1(double mutation_prob);
    void Mutation2(double mutation_prob);
    void Mutation3(double mutation_prob);
    void Mutation4(double mutation_prob);

    void Crossover(double crossover_prob);

    void Check();

    private:

    std::vector<Path> m_population;
    std::vector<City> m_cities;
    unsigned int m_N;
    Random m_rnd;
    
};

bool Compare(Path a, Path b);

#endif