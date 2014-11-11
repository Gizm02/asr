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

    Context<SimpleOptimizer> context();
    ifstream file("material/u3/probe1.ascii.txt");

    string line;
    vector<double> energies;
    while(getline(file,line)){
        energies.push_back(strtod(line.c_str(),NULL));
    }


/********************************************//**
 *  Read in data from probe1.ascii here, initialize needed objects etc.
 ***********************************************/
    return 0;
}
