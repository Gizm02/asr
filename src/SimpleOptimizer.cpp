#include "SimpleOptimizer.h"
#include <iostream>
#include <stdexcept>/**< For use of at(...) member method of std::array or rather std::vector. This enables throwing of exceptions by at(...) when array boundaries are hurt.*/
#include <assert.h>
using namespace std;
SimpleOptimizer::SimpleOptimizer()
{
    //ctor
}

template <class Optimizer>
void optimize(Context<Optimizer>* context,Solution* solution) {
    vector<double> energies=context->getEnergies();
    size_t S=static_cast<size_t>(energies.size());

    ///Test if the vectors are copied correctly
    for(int i=0;i<S;i++) {
        if(energies.at(i)!=context->getEnergies().at(i)) {
            cout<<"Vector copying did not work!"<<endl;
            exit(EXIT_FAILURE);
        }
    }
    double mean=0;
    ///Set up the cost matrix
    for(int i=0;i<(K-2);i++) {
        for(int j=i+1;j<(K-1);j++) {
            ///Determine the mean for the intervall [t_i,t_j]
            for(int k=0;k<(j-i);k++) {
                mean+=energies.at(i+k);
            }
            mean*=1.0/(j-i);
            assert(mean>0);
            double localCost=0;
            for(int k=0;k<(j-i);k++) {
                localCost+=context->h(energies.at(i+k),mean);
            }
            costs.push_back(cost);
        }
    }
    double globalCosts=1;
    double optimalCosts=0;
    for(int i=0;i<(K-2);i++) {
        for(int j=i+1;j<(K-1);j++) {
            globalCosts=costs.at(i*K+j)+costs.at(j*K+);
            optimalCosts=((globalCosts<optimalCosts)||i==0)?globalCosts:optimalCosts;
        }
    }
}
SimpleOptimizer::~SimpleOptimizer()
{
    //dtor
}
