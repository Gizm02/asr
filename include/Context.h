
#ifndef CONTEXT_H
#define CONTEXT_H
#include <vector>
#include <cmath>
#include "Solution.h"
#include "SimpleOptimizer.h"
#define K 3 /**< Total number of segments that have to be determined by the start-stop-detection. */
#define T (K+1) /**< Total number of acoustic feature vectors that are taken into account. */

typedef double numeric;

template <class Optimizer>/**< This template variable stores the used algorithm. */
class Context
{
//Using class here as typename is irrelevant but outlines the most that a class is to be expected for optimizer

    public:
        //Be careful, is an empty vector, elements must be added via push_back(T)

        //double computeOptimum { simop.}
        Context(Optimizer& opt,Solution& sol,std::vector<numeric>& en):energies(en),optimizer(opt),solution(sol) {};
        Context();
        virtual ~Context();

        /*! \brief  This function optimizes the segmentation of the input vectors.
        *
        * \return  The optimal distribution of the input vectors among K intervals.
        *
        */
        void setEnergies(std::vector<numeric> energies);
        std::vector<numeric>& getEnergies();/**< Getter function for the energies stored by the context-obj. */

        /*! \brief  This function determines the local costs for inserting the vector x into a certain interval.
        *
        * \param   x   An acoustic feature vector
        * \param   x_mean The arithmetic mean of the acoustic feature vectors within a certain interval.
        * \return  h(x,x_mean)=(x-x_{mean})^2
        *
        */
        numeric h(numeric x,numeric x_mean);
        void optimize();
    protected:
    private:
        std::vector<numeric>& energies;/**< This variable stores all the energies x_1,...,x_T */
        Optimizer& optimizer;/**< This represents the chosen algorithm. Must be determined/chosen at compile time. */
        Solution& solution;/**< Pointer to an object that stores produced result context. */
};




template <class Optimizer>
Context<Optimizer>::~Context()
{
    //dtor
}

template <class Optimizer>
numeric Context<Optimizer>::h(numeric x,numeric x_mean) {
    return ((pow((x-x_mean),2)));
}

template <class Optimizer>
void Context<Optimizer>::optimize() {
    optimizer.optimize(*this,solution);/**< *this to cast this (Context<Optimizer>* const) into a reference. */
}

template <class Optimizer>
void Context<Optimizer>::setEnergies(std::vector<numeric> energies){
    this->energies = energies;
}
template <class Optimizer>
std::vector<numeric>& Context<Optimizer>::getEnergies() {
    return energies;
}
#endif // CONTEXT_H

