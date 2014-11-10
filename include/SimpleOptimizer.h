#ifndef SIMPLEOPTIMIZER_H
#define SIMPLEOPTIMIZER_H
#include <stdlib.h>
#include <stdexcept>/**< For use of at(...) member method of std::array or rather std::vector. This enables throwing of exceptions by at(...) when array boundaries are hurt.*/
#include "Context.h"

class SimpleOptimizer
{
    public:
        SimpleOptimizer();
        virtual ~SimpleOptimizer();

        /** \brief This method optimizes the problem given by the context-obj.
         *
         * \param context Provides input information.
         * \param solution Stores solution context, e.g. number of needed multiplications, the solution itself etc.
         *
         */
        void optimize(Context<SimpleOptimizer>* context,Solution* solution);
    protected:
    private:
        std::vector<double> costs;
};

#endif // SIMPLEOPTIMIZER_H
