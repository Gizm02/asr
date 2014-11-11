#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>

#include "Context.h"
#include "SimpleOptimizer.h"
#include "Solution.h"

using namespace std;


int main()
{

    ifstream file("material/u3/probe1.ascii.txt");

    if(!file) { exit(EXIT_FAILURE);}
    string line;
    vector<double> energies;
    while(getline(file,line)){
        energies.push_back(strtod(line.c_str(),NULL));
    }
    SimpleOptimizer simp;
    Solution sol;
    Context<SimpleOptimizer> context(simp,sol,energies);
    simp.optimize(context,sol);
    //context.setEnergies(energies);
    /*
    context.setEnergies(energies);
    vector<double>& test = context.getEnergies();
    cout << test.first() << endl;
    */


/********************************************//**
 *  Read in data from probe1.ascii here, initialize needed objects etc.
 ***********************************************/

    return 0;
}
