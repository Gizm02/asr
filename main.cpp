#include <iostream>
#include "Context.h"
#include "SimpleOptimizer.h"
#include "Solution.h"
#include "gtest/gtest.h"
using namespace std;


int main()
{
    ASSERT_TRUE(1>0)<<"Das ist nicht wahr.";
    Context<SimpleOptimizer> context();
    float a; /*!< Detailed description after the member */
    cout << "Hello world!" << endl;
    return 0;
}
