#include "../include/TimeAlignment.h"
#include <fstream>
#include <iostream> 
	

using namespace std;
/*
class TimeAlignment{
	public:
		TimeAlignment(string hypo_file, string ref_file, vector<double> weights);
		void computeDistanceRec();
		void computeDistanceRecMemoi();
		void computeDistanceDP();
	private:
		vector<double> reference;
		vector<double> hypothesis;
		vector<vector<double> > cost_matrix;
		vector<vector<pair<int,int> > > backtrack_matrix;
		vector<double> weights;
		
		int calculation_counter;

}
*/
TimeAlignment::TimeAlignment(string hypo_filename, string ref_filename, vector<double> w){
	ifstream hypo_file(hypo_filename);
	ifstream ref_file(ref_filename);
	weights = w;
	
	calculation_counter = 0;

	if(!hypo_file) exit(EXIT_FAILURE);
	if(!ref_file) exit(EXIT_FAILURE);

	string line;
	while(getline(hypo_file,line)){
        hypothesis.push_back(strtod(line.c_str(),NULL));
    }

	while(getline(ref_file,line)){
        reference.push_back(strtod(line.c_str(),NULL));
    }
	
	vector<double> buffer;
	cost_matrix.resize(hypothesis.size(), buffer);

	for (vector< vector<double> >::iterator it = cost_matrix.begin(); it != cost_matrix.end(); it++){
		it->resize(reference.size(), 0.0);
	}
	
	pair<int, int> pairBuffer(0,0);
	vector<pair<int,int> > pairVectorBuffer;
	backtrack_matrix.resize(hypothesis.size(), pairVectorBuffer);
	for (vector< vector<pair<int,int> > >::iterator it = backtrack_matrix.begin(); it != backtrack_matrix.end(); it++){
		it->resize(reference.size(), pairBuffer);
	}


}

void TimeAlignment::computeDistanceRec(){

}
void TimeAlignment::computeDistanceRecMemoi(){


}
void TimeAlignment::computeDistanceDP(){


}
