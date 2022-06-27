#include "TravellingSalesman.h"
#include "Path.h"
#include "City.h"
#include <fstream>
#include <string>
#include <vector>
#include <errno.h>
#include <algorithm>
#include <iostream>

TravellingSalesman::~TravellingSalesman() {}
TravellingSalesman::TravellingSalesman(const std::string &filename) {

    m_rnd.Init();

    std::ifstream in(filename);

    if(!in) 
    {
        std::error_code the_error(errno, std::system_category());
        std::cerr << "Error opening" << filename <<", error code: " << the_error.message() << std::endl;
        exit(-1);
    }

    while(in.good()) {
        City tmp;
        in >> tmp; //an input file must be "city label" "x" "y"
        m_cities.push_back(tmp);
    }

}

std::vector<Path>& TravellingSalesman::GetPopulation() { return m_population;}

void TravellingSalesman::GeneratePopulation() {

    //std::cout << "Generating population.... ";

    m_N = std::pow( m_cities.size(),2 );

    std::vector<City> cities = m_cities;

    for(unsigned int i=0; i<m_N; ++i)  {
        std::random_shuffle(cities.begin()+1,cities.end());
        Path p(cities);
        m_population.push_back(p);
    }

    //std::cout << "Population generated" << std::endl;
}

unsigned int& TravellingSalesman::GetPopDim() { return m_N;}

void TravellingSalesman::Mutation1(double mutation_prob) {

    for(int path_index=0; path_index<(int)m_population.size();++path_index) {

        if(m_rnd.Rannyu()<mutation_prob) {

            unsigned int i1,i2;
    
            do {
                i1 = static_cast<int>(m_rnd.Rannyu(1,m_cities.size()));
                i2 = static_cast<int>(m_rnd.Rannyu(1,m_cities.size()));
            } while(i1==i2 );

            m_population[path_index].Swap(i1,i2);
        }
    }
}

void TravellingSalesman::Mutation2(double mutation_prob) {

    for(int path_index=0; path_index<(int)m_population.size();++path_index) {

        if(m_rnd.Rannyu()<mutation_prob) {

            unsigned int shift = static_cast<int>(m_rnd.Rannyu(0,m_cities.size()-2));       // to m_cities.size()-2 because I dont want to shift the first element and 
                                                                                    //I want I can shift every time the function is called: if shift is m_city.size()-1 
                                                                                    //and the first element is inamovible I cant shift

            unsigned int last = static_cast<int>(m_rnd.Rannyu(2,m_cities.size()-shift));    //extract the last element to shift, from the third to the dim-shift 

            unsigned int first = static_cast<int>(m_rnd.Rannyu(1,last-1));                  //the first element to be shifted cant be the first [0], and I want to shif at least a size 1 vector

            m_population[path_index].Shift(shift,first,last);
        }

    }

}

void TravellingSalesman::Mutation3(double mutation_prob) {

    for(int path_index=0; path_index<(int)m_population.size();++path_index) {

        if(m_rnd.Rannyu()<mutation_prob) {

            unsigned int first = static_cast<int>(m_rnd.Rannyu(1,m_cities.size()-1));
            unsigned int last = static_cast<int>(m_rnd.Rannyu(first+1,m_cities.size()));

            unsigned int r = static_cast<int>(m_rnd.Rannyu(first+1,last-1));

            m_population[path_index].Rotate(first,last,r);
        }

    }

}

void TravellingSalesman::Mutation4(double mutation_prob) {

    for(int path_index=0; path_index<(int)m_population.size();++path_index) {

        if(m_rnd.Rannyu()<mutation_prob) {

            unsigned int first = static_cast<int>(m_rnd.Rannyu(1,m_cities.size()-1));
            unsigned int last = static_cast<int>(m_rnd.Rannyu(first+1,m_cities.size()));

            m_population[path_index].Reverse(first,last);
        }
    }

}

Path TravellingSalesman::BestPath() {

    Path best(m_population[0].GetPath()); 

    for(int i=1;i<(int)m_population.size();++i) {

        if(best.Measure() > m_population[i].Measure() ) best = m_population[i];

    }

    return best;

}

void TravellingSalesman::Check() {

    if(m_population.size() != m_N ) {

            std::cerr << "The dimension of the population is changed!!" << std::endl;
            exit(-1);
    }

    for(int i=0; i< (int)m_population.size(); ++i) {

        if(m_population[i].GetPath()[0].GetLabel() != m_cities[0].GetLabel()) {
            
            std::cerr << "The first city visitated is changed!!" << std::endl;
            exit(-1);

        }

    for(int j=1; j<(int)m_cities.size(); j++){
            int check=0;
            for(int k=1; k<(int)m_cities.size(); k++){
                if(m_cities[j].GetLabel()==m_population[i].GetPath()[k].GetLabel()) check+=1;
            }

            if (check!=1){
                std::cerr<<"The city in position "<<j<<" appears "<<check<<" times in the path" << std::endl;
                exit(-3);
            }
        }

    }
    
}

void TravellingSalesman::Order() {

    std::sort(m_population.begin(), m_population.end(), Compare);

}

bool Compare(Path a, Path b) {return a.Measure() < b.Measure();}

void TravellingSalesman::Crossover(double crossover_prob) {

    int dim = m_N;
    std::vector<int> extracted(dim);
    double exp = 7.;

    for( int i=0; i<dim ; ++i ) {

        unsigned int index = static_cast<int>( ((m_N) * std::pow( m_rnd.Rannyu(), exp)) );
        extracted[i] = index;
    }

    std::vector<Path> sons(dim);

    //std::cout << "b" << std::endl;

    for( int i=0; i<(int)extracted.size();i+=2) {

        //std::cout << i << " " << (int)extracted.size() << std::endl; 

        //std::cout << extracted[i] << " " << extracted[i+1] << std::endl;

        if(m_rnd.Rannyu()<crossover_prob) {

            Path parent1 = m_population[extracted[i]];
            Path parent2 = m_population[extracted[i+1]];

            //std::cout << m_population.size() << " " << m_N <<  std::endl;

            unsigned int cut_point =  m_rnd.Rannyu(1,(int)m_cities.size()-1);

            std::vector<City> son1( parent1.GetPath().begin(), parent1.GetPath().begin() + cut_point);
            std::vector<City> son2( parent2.GetPath().begin(), parent2.GetPath().begin() + cut_point);

            //std::cout << "b" << std::endl;

            for(int j=1; j<(int)m_cities.size(); ++j) {

                City s1 = parent2.GetPath()[j];
                City s2 = parent1.GetPath()[j];

                if( std::find( son1.begin()+1, son1.end(), s1 ) == son1.end() ) son1.push_back(s1);
                if( std::find( son2.begin()+1, son2.end(), s2 ) == son2.end() ) son2.push_back(s2);

            }

            sons[i].SetPath(son1);
            sons[i+1].SetPath(son2);

        }else{

            sons[i].SetPath(m_population[i].GetPath());
            sons[i+1].SetPath(m_population[i+1].GetPath());
        }

        //std::cout << m_population.size() << " " << sons.size() << std::endl;
    
    }

    for(unsigned int i=0; i<(unsigned int)m_population.size(); ++i) m_population[i].SetPath(sons[i].GetPath());
}

