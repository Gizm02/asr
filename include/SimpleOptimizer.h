#ifndef SIMPLEOPTIMIZER_H
#define SIMPLEOPTIMIZER_H
#include <stdlib.h>
#include <array>
#include "Context.h"

/*template <class Optimizer>
class Context<Optimizer>;
*/
class SimpleOptimizer
{
    public:
        SimpleOptimizer():costs(T*T) { };
        virtual ~SimpleOptimizer();

        /** \brief This method optimizes the problem given by the context-obj.
         *
         * \param context Provides input information.
         * \param solution Stores solution context, e.g. number of needed multiplications, the solution itself etc.
         *
         */

        void optimize(const Context<Optimizer>& context,Solution& solution);


        /** \brief  Computes the mean of acoustic feature vectors within a fixed interval.
         *
         * \param   energies Reference to a reference containing the acoustic feature vectors that are taken into account.
         * \param   i The lower index of lower interval bound.
         * \param   j The bigger index of the upper interval bound.
         * \return The mean of the vectors.
         *
         */
        numeric getMean(const std::vector<numeric>& energies, int i, int j);

        std::vector<numeric> getCosts();
    protected:
    private:
        std::vector<numeric> costs;/**< The cost matrix. */
};


#endif // SIMPLEOPTIMIZER_H
