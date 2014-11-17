
#include "SimpleOptimizer.h"
#include <iostream>
#include <stdexcept>/**< For use of at(...) member method of std::array or rather std::vector. This enables throwing of exceptions by at(...) when array boundaries are violated.*/
#include <assert.h>
#define DEBUG 1


using namespace std;

template <class Optimizer>
void SimpleOptimizer::optimize(const Context<Optimizer>& context,Solution& solution) {
    vector<numeric> energies=context.getEnergies();
    size_t T=static_cast<size_t>(context.getEnergies().size());
    #if DEBUG>0
    ///Test if the vectors are copied correctly
    for(int i=0;i<T;i++) {
        if(energies.at(i)!=context.getEnergies().at(i)) {
            cout<<"Vector copying did not work! FAILURE AT FILE"<< __FILE__<<",line "<<__LINE__ <<endl;
            exit(EXIT_FAILURE);
        }
    }
    #endif // DEBUG
    numeric mean=0;
    ///Set up the cost matrix
    for(int i=0;i<(T-2);i++) {
        for(int j=i+1;j<(T-1);j++) {
            ///Determine the mean for the intervall [t_i,t_j]
            mean=this->getMean(energies,i,j);
            #if DEBUG>0
            assert(mean>0);
            #endif
            numeric localCost=0;
            for(int k=0;k<(j-i);k++) {
                localCost+=context.h(energies.at(i+k),mean);
            }
            costs.push_back(i*K+j)=localCost;
        }
    }
    numeric globalCosts;/**< Stores the global cost for a segmentation. */
    numeric optimalCosts;/**< Stores the optimal cost found during iteration. */
    for(int i=0;i<(T-2);i++) {
        for(int j=i+1;j<(T-1);j++) {
            globalCosts=costs.at(i)+costs.at(i*K+j)+costs.at(j*K+K);
            optimalCosts=((globalCosts<optimalCosts)||i==0)?globalCosts:optimalCosts;
        }
    }
    solution.setSolution(optimalCosts);/**< Store the result in the solution obj. */
}

vector<numeric> SimpleOptimizer::getCosts() {
    return costs;
}

numeric SimpleOptimizer::getMean(const vector<numeric>& energies, int i, int j) {
    numeric mean=0;
    for(int k=0;k<=(j-i);k++) {
        mean+=energies.at(i+k);
    }
    mean*=1.0/(j-i);
    return mean;
}



SimpleOptimizer::~SimpleOptimizer()
{
    //dtor
}

