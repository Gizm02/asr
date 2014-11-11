#include "Context.h"
/** \brief By using this define, it is easier to exchange the Optimizers we want to apply on our context object.
 *
 *  Example usage: #define OPTIMIZER MyOptimizerImplementation
 */
#define OPTIMIZER   SimpleOptimizer
using namespace std;

template <class Optimizer>
double Context<Optimizer>::h(double x,double x_mean) {
    return ((pow((x-x_mean),2)));
}

template <class Optimizer>
double Context<Optimizer>::optimize() {

    return 0;
}

template <class Optimizer>
vector<double>& Context<Optimizer>::getEnergies() {
    return energies;
}

template <class Optimizer>
Context<Optimizer>::~Context()
{
    //dtor
}
