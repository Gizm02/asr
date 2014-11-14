/*!
 * This class encapsulates solution context produced by the applied algorithms.
 */

#ifndef SOLUTION_H
#define SOLUTION_H


typedef double numeric;

class Solution
{
    public:
        /** \brief The main ctor of this class.
         *
         * \param   solution    The result the Solution-object supposed to store.
         *
         */
        Solution(numeric sol):solution(sol),multCount(0) {};
        Solution():Solution(static_cast<numeric>(0)) { };/**< Ctor delegation */


        virtual ~Solution();

        /** \brief Returns the solution computed by the chosen optimizer object.
         *
         * \return Computed solution.
         *
         */
        numeric getSolution();
        void setSolution(numeric solution);
    protected:
    private:
        numeric solution;/**< Stores the result computed by the chosen optimizer/algorithm object. */
        unsigned int multCount;/**< The number of multiplications needed for computing the optimum */
};

#endif // SOLUTION_H
