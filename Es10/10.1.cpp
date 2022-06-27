#include "TravellingSalesman.h"
#include "random.h"
#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>
#include <algorithm>

int main(int argc, char* argv[]) {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::string filename;

    if(argc >= 2) filename = argv[1];
    else{
        std::cout<<"Insert input file:";
        std::cin >> filename;
    }

    int N_gen=500;

    double div= N_gen/100.;
    int N_migr=5;
    double mutation_prob = 0.1;
    double crossover_prob = 0.5;

    Random rnd;
    rnd.Init(world_rank+1);

    TravellingSalesman TS(filename, world_rank);

    TS.GeneratePopulation();

    std::vector<Path> bests(world_size);

    for(int i=0; i<world_size; ++i) bests[world_rank]= TS.BestPath();

    for(int i=0; i<N_gen; ++i) {

        if( world_rank == 0 && i%(int)(div) == 0)  std::cout << (double)i/double(div) << "%  "<< std::endl;

        if(/*i%N_migr==0*/ false) {

            std::vector<int> proc;
            for(int i=0; i<world_size; ++i) proc.push_back(i);
            std::random_shuffle(proc.begin(), proc.end());

            int proc_[world_size];

            for(int i=0; i<world_size; ++i) proc_[i] = proc[i];

            MPI_Bcast(proc_, world_size, MPI_INTEGER, 0, MPI_COMM_WORLD);

            TS.Order();

            for(int j=0; j<(int)TS.GetCitiesNum();++j) {

                int label = TS.GetPopulation()[0].GetPath()[j].GetLabel();
                double x = TS.GetPopulation()[0].GetPath()[j].GetCoords().GetX();
                double y = TS.GetPopulation()[0].GetPath()[j].GetCoords().GetY();

                MPI_Request req1, req2, req3;
                MPI_Status stat1, stat2, stat3, stat4, stat5, stat6;

                for(int k=0; k<world_size; k+=2) {

                    if(world_rank==proc_[k]){

                        MPI_Isend(&label, 1, MPI_INTEGER, proc_[k+1], 1, MPI_COMM_WORLD, &req1);
                        MPI_Recv(&label, 1, MPI_INTEGER, proc_[k+1], 2,  MPI_COMM_WORLD, &stat2);

                    }else if(world_rank==proc_[k+1]){

                        MPI_Send(&label, 1, MPI_INTEGER, proc_[k], 2, MPI_COMM_WORLD);
                        MPI_Recv(&label, 1, MPI_INTEGER, proc_[k], 1,  MPI_COMM_WORLD, &stat1);

                    }

                }

                for(int k=0; k<world_size; k+=2) {

                    if(world_rank==proc_[k]){

                        MPI_Isend(&x, 1, MPI_DOUBLE_PRECISION, proc_[k+1], 3, MPI_COMM_WORLD, &req2);
                        MPI_Recv(&x, 1, MPI_DOUBLE_PRECISION, proc_[k+1], 4,  MPI_COMM_WORLD, &stat4);

                    }else if(world_rank==proc_[k+1]){

                        MPI_Send(&x, 1, MPI_DOUBLE_PRECISION, proc_[k], 4, MPI_COMM_WORLD);
                        MPI_Recv(&x, 1, MPI_DOUBLE_PRECISION, proc_[k], 3,  MPI_COMM_WORLD, &stat3);

                    }
                }

                for(int k=0; k<world_size; k+=2) {

                    if(world_rank==proc_[k]){

                        MPI_Isend(&y, 1, MPI_DOUBLE_PRECISION, proc_[k+1], 5, MPI_COMM_WORLD, &req3);
                        MPI_Recv(&y, 1, MPI_DOUBLE_PRECISION, proc_[k+1], 6,  MPI_COMM_WORLD, &stat6);

                    }else if(world_rank==proc_[k+1]){

                        MPI_Send(&y, 1, MPI_DOUBLE_PRECISION, proc_[k], 6, MPI_COMM_WORLD);
                        MPI_Recv(&y, 1, MPI_DOUBLE_PRECISION, proc_[k], 5,  MPI_COMM_WORLD, &stat5);

                    }
                }

                TS.GetPopulation()[0].GetPath()[j].SetLabel(label);
                TS.GetPopulation()[0].GetPath()[j].GetCoords().SetX(x);
                TS.GetPopulation()[0].GetPath()[j].GetCoords().SetY(y);
            
            }
            
        }

        TS.Order();
        TS.Crossover(crossover_prob);

        TS.Mutation1(mutation_prob);
        TS.Mutation2(mutation_prob);
        TS.Mutation3(mutation_prob);
        TS.Mutation4(mutation_prob);
 
        //TS.Check();

        if( bests[world_rank].Measure() > TS.BestPath().Measure()) bests[world_rank].SetPath(TS.BestPath().GetPath());

    }
    
    for(int j=0; j<world_size; j++) {

        if(j==world_rank) {

            std::string out_file= "output" + std::to_string(world_rank) + ".out";
            std::ofstream out(out_file);

            for( int i=0; i<(int)bests[world_rank].GetPath().size(); ++i) {
                out << bests[world_rank].GetPath()[i].GetLabel() << " " 
                    << bests[world_rank].GetPath()[i].GetCoords().GetX() << " " 
                    << bests[world_rank].GetPath()[i].GetCoords().GetY() << std::endl;
            }
            out << bests[world_rank].GetPath()[0].GetLabel() << " " 
                << bests[world_rank].GetPath()[0].GetCoords().GetX() << " " 
                << bests[world_rank].GetPath()[0].GetCoords().GetY() << std::endl;

            out.close();
        }

    }

    MPI_Finalize();

    return 0;

}