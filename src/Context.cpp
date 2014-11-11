#include "Context.h"
/** \brief By using this define, it is easier to exchange the Optimizers we want to apply on our context object.
 *
 *  Example usage: #define OPTIMIZER MyOptimizerImplementation
 */

using namespace std;
/*

Context<Optimizer>::Context() {}


template <class Optimizer>
Context<Optimizer>::~Context()
{
    //dtor
}

template <class Optimizer>
double Context<Optimizer>::h(double x,double x_mean) {
    return ((pow((x-x_mean),2)));
}

template <class Optimizer>
double Context<Optimizer>::optimize() {
    return 0;
}

template <class Optimizer>
void Context<Optimizer>::setEnergies(std::vector<double> energies){
    this->energies = energies;
}
template <class Optimizer>
vector<double>& Context<Optimizer>::getEnergies() {
    return energies;
}

*/
