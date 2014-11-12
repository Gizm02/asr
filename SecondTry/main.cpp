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

    mean/=static_cast<double>(j-i+1);

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
    array<array <double,SIZE>,SIZE> means;

    for(int i=0;i<T;i++) {
        means[i][i] = energies[i];
        for(int j=i+1;j<T;j++) {
            double localCost, mean;
            means[i][j] = (energies[j] + (j-i) * means[i][j-1]) / (j-i+1);
            localCost=0;
            for(int k=0;k<=(j-i);k++) {
                localCost+=h(energies[i+k],means[i][j]);
            }
            costs[i][j]=localCost;
        }
    }
    double optimalCosts;
    double globalCosts=0;


    vector<double> optimalIndexes(4);

    vector<double> optimalMeans(K+1);
    optimalMeans.at(0)=0;
    optimalMeans.at(K)=0;

    optimalIndexes.at(0)=0;
    optimalIndexes.at(K)=T;

    for(int i=0;i<T;i++) {
        for(int j=i+1;j<T;j++) {
            globalCosts=costs[0][i]+costs[i+1][j]+costs[j+1][T-1];
            if(globalCosts<optimalCosts) {
                cout<<"New minimal costs are:"<<globalCosts<<endl;
                //optimalCosts = globalCosts;
                optimalMeans.at(0) = means[0][i];
                optimalMeans.at(1) = means[i+1][j];
                optimalMeans.at(2) = means[j+1][T-1];
                optimalIndexes.at(1) = i+1;/**< The indexing of the acoustic vectors start by 1 but i and j have array semantics (so we need to increment). */
                optimalIndexes.at(2) = j+1;
            }
            optimalCosts=((globalCosts<optimalCosts)||(i==0&& j==1))?globalCosts:optimalCosts;
        }
    }

    cout << "Optimal Costs: "<<optimalCosts << " Optimal Indeces i and j: "<< optimalIndexes.at(1) << " " << optimalIndexes.at(2) << endl;
    cout << "Optimal means: "  << endl << " x_{0,i} = " << optimalMeans.at(1) << endl << " x_{i+1,j} = " << optimalMeans.at(2) << endl<< " x_{j+1,T-1} =" << optimalMeans.at(3) << endl;
    return 0;
}
