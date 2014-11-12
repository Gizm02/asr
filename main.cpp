#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG 1
#define K 3

using namespace std;
double h(double x,double x_mean) {
    double val=((pow((x-x_mean),2)));
    
    return val;
}
double getMean(vector<double>& energies, size_t i, size_t j){
    double mean=0;
    for(int k=0;k<=(j-i);k++) {
        mean+=energies.at(i+k);
    }
    mean*=1.0/(j-i);
    return mean;
}
int main()
{
    ifstream file("material/u3/probe1.ascii.txt");

    if(!file) { exit(EXIT_FAILURE);}
    string line;
    vector<double> energies;
    while(getline(file,line)){
        energies.push_back(strtod(line.c_str(),NULL));
    }
    /*
    context.setEnergies(energies);
    vector<double>& test = context.getEnergies();
    cout << test.first() << endl;
    */

    ///Test if the vectors are copied correctly
    double mean=0;
    size_t T = energies.size();
    ///Set up the cost matrix
    vector<double> costs(T*T);
    for(int i=0;i<(T-2);i++) {
        for(int j=i+1;j<(T-1);j++) {
            ///Determine the mean for the intervall [t_i,t_j]
            mean=getMean(energies,i,j);
            #if DEBUG>0
            assert(mean!=0);
            #endif
            double localCost=0;
            for(int k=0;k<(j-i);k++) {
                localCost+=h(energies.at(i+k),mean);
                
            }
            cout << localCost << " " ;
            costs.at(i*K+j)=localCost;
        }
        cout << endl;
    }
    double globalCosts;/**< Stores the global cost for a segmentation. */
    double optimalCosts;/**< Stores the optimal cost found during iteration. */
    vector<double> optimalIndexes(K+1,0);
    optimalIndexes.at(0)=0;
    optimalIndexes.at(K)=T;
    for(int i=0;i<(T-2);i++) {
        for(int j=i+1;j<(T-1);j++) {
            globalCosts=costs.at(i)+costs.at(i*K+j)+costs.at(j*K+K);
            if ( globalCosts < optimalCosts){
                //optimalCosts = globalCosts;
                optimalIndexes.at(1) = i;
                optimalIndexes.at(2) = j;
            }
            optimalCosts=((globalCosts<optimalCosts)||i==0&& j==1)?globalCosts:optimalCosts;
        }
    }

    cout << optimalCosts << " " << optimalIndexes.at(1) << " " << optimalIndexes.at(2) << endl;
    return 0;
}
