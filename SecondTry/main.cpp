#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <array>
#define SIZE 15
#define K 3
#define DEBUG 1

using namespace std;

double h(double x,double x_mean) {
    return (pow((x-x_mean),2));
}

double getMean(vector<double>& energies, unsigned int i, unsigned int j){
    double mean=0;
    for(int k=0;k<=(j-i);++k) {
        mean+=energies[i+k];
    }
    mean=mean/(j-i+1);
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

///Test if the vectors are copied correctly
    double mean=0;
    const size_t T = SIZE;
    #if DEBUG>0
    cout<<"T is: "<<T<<endl;
    #endif // DEBUG
    array<array <double,SIZE>,SIZE> costs;
    for(int i=0;i<T;i++) {
        for(int j=i+1;j<T;j++) {
            double localCost, mean;
            mean=getMean(energies,i,j);
            localCost=0;
            for(int k=0;k<=(j-i);k++) {
                localCost+=h(energies[i+k],mean);
            }
            costs[i][j]=localCost;
        }
    }
    double optimalCosts;
    double globalCosts=0;

    vector<double> optimalIndexes(SIZE);
    optimalIndexes.at(0)=0;
    optimalIndexes.at(K)=T;



    for(int i=0;i<T;i++) {
        for(int j=i+1;j<T;j++) {
            globalCosts=costs[0][i]+costs[i+1][j]+costs[j+1][T-1];
            if(globalCosts<optimalCosts) {
                cout<<"New minimal costs are:"<<globalCosts<<endl;
                //optimalCosts = globalCosts;
                optimalIndexes.at(1) = i;
                optimalIndexes.at(2) = j;
            }
            optimalCosts=((globalCosts<optimalCosts)||(i==0&& j==1))?globalCosts:optimalCosts;
        }
    }

    cout << "Optimal Costs: "<<optimalCosts << " Optimal Indeces i and j: "<< optimalIndexes.at(1) << " " << optimalIndexes.at(2) << endl;

    return 0;
}
