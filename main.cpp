#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "Context.h"
#include "SimpleOptimizer.h"
#include "Solution.h"
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
<<<<<<< HEAD
    mean/=static_cast<double>(j-i);
=======
    mean*=1.0/(j-i+1);
>>>>>>> e95af8e68fcc9fff08173648a68f13088c14e622
    return mean;
}
int main()
{
    vector<double> energies;
     string name;
    #if DEBUG>0
        name="material/u3/training.ascii.txt";
    #else
        name="material/u3/probe1.ascii.txt";
    #endif
    ifstream file(name);

    if(!file) { exit(EXIT_FAILURE);}
    string line;

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
    #if DEBUG>0
    cout<<"T is: "<<T<<endl;
    #endif // DEBUG
    ///Set up the cost matrix
    vector<double> costs(T*T);
    for(int i=0;i<T;i++) {
        cout << "HALLO" << endl;
        for(int j=i;j<T;j++) {
            ///Determine the mean for the intervall [t_i,t_j]

            mean=getMean(energies,i,j);
            /*#if DEBUG>0
            assert(mean!=0);
            #endif*/
            double localCost=0;
            for(int k=0;k<=(j-i);k++) {
                localCost+=h(energies.at(i+k),mean);
                //cout<<localCost<<" ";
            }
        //    cout<<endl;
            costs.at(i*T+j)=localCost;
            mean = getMean(energies,i,j);
            costs.at(i*T+j) = h(energies.at(i),mean);
            cout << mean << " " << costs.at(i*T+j) << endl;


        }
        cout << endl;
    }
    #if DEBUG>0
    for(const auto &element: costs) {
       // cout<<element<<" ";
    }
    #endif // DEBUG
    double globalCosts;/**< Stores the global cost for a segmentation. */
    double optimalCosts;/**< Stores the optimal cost found during iteration. */
    vector<double> optimalIndexes(K+1,0);
    optimalIndexes.at(0)=0;
    optimalIndexes.at(K)=T;
    for(int i=0;i<(T-2);i++) {
        for(int j=i+1;j<(T-1);j++) {
<<<<<<< HEAD
            globalCosts=costs.at(i)+costs.at((i+1)*T+j)+costs.at((j+1)*T+T);
=======
            globalCosts=costs.at(i)+costs.at(i*T+j)+costs.at(j*T+T);
>>>>>>> e95af8e68fcc9fff08173648a68f13088c14e622
            if ( globalCosts < optimalCosts){
                cout<<"New minimal costs are:"<<globalCosts<<endl;
                //optimalCosts = globalCosts;
                optimalIndexes.at(1) = i;
                optimalIndexes.at(2) = j;
            }

            optimalCosts=((globalCosts<optimalCosts)||i==0&& j==1)?globalCosts:optimalCosts;

        }
    }

    cout << "Optimal Costs: "<<optimalCosts << " Optimal Indeces i and j: "<< optimalIndexes.at(1) << " " << optimalIndexes.at(2) << endl;
    for (int i = 0; i < costs.size() ; i++){
        for (int n = 1; n < 6; n++){
            if (i == (n * 5)){
                cout << endl;
                break;
            }
        }
        cout << *(costs.begin()+i)<< " " ;
    }
    return 0;
}
