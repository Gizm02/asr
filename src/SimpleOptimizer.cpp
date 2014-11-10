#include "SimpleOptimizer.h"
#include <iostream>
using namespace std;
SimpleOptimizer::SimpleOptimizer()
{
    //ctor
}

template <class Optimizer>
void optimize(Context<Optimizer>* context,Solution* solution) {
    vector<double> energies=context->getEnergies();
    size_t S=static_cast<size_t>(energies.size());

    ///Test suit
    for(int i=0;i<S;i++) {
        if(energies.at(i)!=context->getEnergies().at(i)) {
            cout<<"Vector copying did not work!"<<endl;
            exit(EXIT_FAILURE);
        }
    }
    ///Set up the cost matrix
    for(int i=0;i<(K-2);i++) {
        for(int j=i+1;j<(K-1);j++) {
            cout <<"TOLL"<<endl;
        }
    }
}
SimpleOptimizer::~SimpleOptimizer()
{
    //dtor
}
