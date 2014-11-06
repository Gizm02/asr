#include "Context.h"
/** \brief By using this define, it is easier to exchange the Optimizers we want to apply on our context object.
 *
 *  Example usage: #define OPTIMIZER MyOptimizerImplementation
 */
#define OPTIMIZER   SimpleOptimizer
using namespace std;
Context::Context()
{
    //ctor
}

Context::~Context()
{
    //dtor
}
