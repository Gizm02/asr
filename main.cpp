#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>

#include "src/Context.h"
#include "src/SimpleOptimizer.h"
#include "src/Solution.h"

using namespace std;


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
