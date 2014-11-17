#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <array>
#define SIZE 146
#define K 3
#define DEBUG 0
using namespace std;
int multCount = 0;
#include "src/Context.h"
#include "src/SimpleOptimizer.h"
#include "src/Solution.h"

typedef double numeric;/**< To easily change the used data type. */

int main()
{

    ifstream file("material/u3/probe1.ascii.txt");/**< Define input file stream obj. */

    if(!file) { exit(EXIT_FAILURE);}
    string line;
    vector<numeric> energies;

    while(getline(file,line)){
        energies.push_back(strtod(line.c_str(),nullptr));/**< Always use nullptr instead of NULL! */
    }
    SimpleOptimizer simp;
    Solution sol;
    Context<SimpleOptimizer> context(simp,sol,energies);
    context.optimize();
    //context.setEnergies(energies);
    /*
    context.setEnergies(energies);
    vector<double>& test = context.getEnergies();
    cout << test.first() << endl;
    */

    return 0;
}
