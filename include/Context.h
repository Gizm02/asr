/**
 * This class encapsulates the application data and uses algorithms to compute the optimal solution for the problem given in the task.
 */

#ifndef CONTEXT_H
#define CONTEXT_H
#include <vector>

class Context
{

    public:
        //Be careful, is an empty vector, elements must be added via push_back(T)
        std::vector<double> energies;/**< This variable stores all the ernergies x_1,...,x_t */
        //double computeOptimum { simop.}
        Context();
        virtual ~Context();
        double computeOptimum(Context* context);
    protected:
    private:
        //Using class here as typename is irrelevant but outlines the most that a class is to be expected for optimizer
        template <class Optimizer>/**< This template variable stores the used algorithm. */
        Optimizer optimizer;/**< This represents the chosen algorithm. Must be determined/chosen at compile time. */
};

#endif // CONTEXT_H
