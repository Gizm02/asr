#ifndef SIMPLEOPTIMIZER_H
#define SIMPLEOPTIMIZER_H

#include <stdexcept>/**< For use of at(...) member method of std::array or rather std::vector. This enables throwing of exceptions by at(...) when array boundaries are hurt.*/

class SimpleOptimizer
{
    public:
        SimpleOptimizer();
        virtual ~SimpleOptimizer();
    protected:
    private:
};

#endif // SIMPLEOPTIMIZER_H
