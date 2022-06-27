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

    TravellingSalesman(int line);
    TravellingSalesman(const std::string &filename);
    TravellingSalesman(const std::string &filename,int line);
    ~TravellingSalesman();

    void SetCities(std::vector<City> cities);

    Path BestPath();
    void GeneratePopulation();

    unsigned int& GetPopDim();
    unsigned int& GetCitiesNum();
    std::vector<Path>& GetPopulation();

    void Order();

    void Mutation1(double mutation_prob);
    void Mutation2(double mutation_prob);
    void Mutation3(double mutation_prob);
    void Mutation4(double mutation_prob);

    void Shuffle(std::vector<City> &c);

    void Crossover(double crossover_prob);

    void Check();

    private:

    std::vector<Path> m_population;
    std::vector<City> m_cities;
    unsigned int m_N;
    unsigned int m_N_c;
    Random m_rnd;
    
};

bool Compare(Path a, Path b);

#endif