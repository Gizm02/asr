#ifndef SIMPLEOPTIMIZER_H
#define SIMPLEOPTIMIZER_H
#include <stdlib.h>
#include "Context.h"

class SimpleOptimizer
{
    public:
        SimpleOptimizer():costs(K) { };
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
        /** \brief  Computes the mean of acoustic feature vectors within a fixed interval.
         *
         * \param   energies Contains the acoustic feature vectors that are taken into account.
         * \param   i The lower index of lower interval bound.
         * \param   j The bigger index of the upper interval bound.
         * \return The mean of the vectors.
         *
         */
        double getMean(std::vector<double> energies, int i, int j);
        std::vector<double> costs;/**< The cost matrix. */
};

#endif // SIMPLEOPTIMIZER_H
