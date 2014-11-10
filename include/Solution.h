/*!
 * This class encapsulates solution context produced by the applied algorithms.
 */

#ifndef SOLUTION_H
#define SOLUTION_H


class Solution
{
    public:
        /** \brief The main ctor of this class.
         *
         * \param   solution    The result the Solution-object supposed to store.
         *
         */
        Solution(double solution);
        Solution():Solution(0){ };/**< Ctor delegation */


        virtual ~Solution();

        /** \brief Returns the solution computed by the chosen optimizer object.
         *
         * \return Computed solution.
         *
         */
        double getSolution();
    protected:
    private:
        double solution;/**< Stores the result computed by the chosen optimizer/algorithm object. */
        unsigned int multCount;/**< The number of multiplications needed for computing the optimum */
};

#endif // SOLUTION_H
