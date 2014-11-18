#include "../include/TimeAlignment.h"
#include <fstream>
#include <iostream> 
#include <cmath>
#include <algorithm>

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

	if(!hypo_file) cout << "Hypo file couldn't be opened" << endl;
	if(!ref_file) cout << "Ref file couldn't be opened" << endl;

	string line;
	while(getline(hypo_file,line)){
        hypothesis.push_back(strtod(line.c_str(),NULL));
    }

	while(getline(ref_file,line)){
        reference.push_back(strtod(line.c_str(),NULL));
    }
	
	vector<double> buffer;
	cost_matrix.resize(reference.size(), buffer);

	for (vector< vector<double> >::iterator it = cost_matrix.begin(); it != cost_matrix.end(); it++){
		it->resize(hypothesis.size(), -1.0);
	}
	
	pair<int, int> pairBuffer(0,0);
	vector<pair<int,int> > pairVectorBuffer;
	backtrack_matrix.resize(hypothesis.size(), pairVectorBuffer);
	for (vector< vector<pair<int,int> > >::iterator it = backtrack_matrix.begin(); it != backtrack_matrix.end(); it++){
		it->resize(reference.size(), pairBuffer);
	}


}

double TimeAlignment::calculate1Norm(int x1, int x2){
	return abs(reference.at(x1) - hypothesis.at(x2));
}

double TimeAlignment::computeDistanceRec(){
	return computeDistanceRec(reference.size()-1, hypothesis.size()-1);
}

double TimeAlignment::computeDistanceRec(int refPos, int hypPos){
	vector<double> prevCosts(3,pow(2,30));
	if (hypPos == 0 ){
		calculation_counter++;
		return calculate1Norm(refPos, hypPos);
	} else if(refPos == 1){
		calculation_counter++;
		prevCosts.at(0) = computeDistanceRec(refPos -0, hypPos -1) + weights[0];
		prevCosts.at(1) = computeDistanceRec(refPos -1, hypPos -1) + weights[1];
		return calculate1Norm(refPos, hypPos) + *(min_element(prevCosts.begin(), prevCosts.end()));
	} else if(refPos == 0){
		calculation_counter++;
		return calculate1Norm(refPos, hypPos) + computeDistanceRec(refPos, hypPos-1) + weights[0];
	} else {
		calculation_counter++;
		prevCosts.at(0) = computeDistanceRec(refPos -0, hypPos -1) + weights[0];
		prevCosts.at(1) = computeDistanceRec(refPos -1, hypPos -1) + weights[1];
		prevCosts.at(2) = computeDistanceRec(refPos -2, hypPos -1) + weights[2];
		return calculate1Norm(refPos, hypPos) + *(min_element(prevCosts.begin(), prevCosts.end()));
	}
}
double TimeAlignment::computeDistanceRecMemoi(){
	return computeDistanceRecMemoi(reference.size()-1, hypothesis.size() -1);
}
double TimeAlignment::computeDistanceRecMemoi(int refPos, int hypPos){
	vector<double> prevCosts(3,pow(2,30));
	if (hypPos == 0 ){
		calculation_counter++;
		cost_matrix[refPos][hypPos] = calculate1Norm(refPos, hypPos);
		return cost_matrix[refPos][hypPos];
	} else if(refPos == 1){
		for (int q = 0; q < 2; q++){
			if (cost_matrix[refPos-q][hypPos-1] == -1){
				calculation_counter++;
				cost_matrix[refPos-q][hypPos-1] = computeDistanceRecMemoi(refPos-q, hypPos-1);
			}
			prevCosts[q] =cost_matrix[refPos-q][hypPos-1] + weights[q];
		}
		calculation_counter++;
		cost_matrix[refPos][hypPos] = calculate1Norm(refPos, hypPos) + *(min_element(prevCosts.begin(), prevCosts.end()));
		return cost_matrix[refPos][hypPos];
	} else if(refPos == 0){	
		calculation_counter++;
		if (cost_matrix.at(refPos).at(hypPos-1) == -1){
			calculation_counter++;
			cost_matrix[refPos][hypPos-1] = computeDistanceRecMemoi(refPos, hypPos - 1);
		}
		prevCosts.at(0) = cost_matrix[refPos][hypPos-1] + weights[0];
		cost_matrix[refPos][hypPos] = calculate1Norm(refPos, hypPos) + prevCosts.at(0);
		return cost_matrix[refPos][hypPos];
	} else {
		for (int q = 0; q < 3; q++){
			if (cost_matrix[refPos-q][hypPos-1] == -1){
				calculation_counter++;
				cost_matrix[refPos-q][hypPos-1] = computeDistanceRecMemoi(refPos-q, hypPos-1);
			}
			prevCosts[q] =cost_matrix[refPos-q][hypPos-1] + weights[q];
		}	
		calculation_counter++;
		cost_matrix[refPos][hypPos] = calculate1Norm(refPos, hypPos) + *(min_element(prevCosts.begin(), prevCosts.end()));
		return cost_matrix[refPos][hypPos];
	}
}

double TimeAlignment::computeDistanceDP(){
	calculation_counter++;
	cost_matrix[0][0] = calculate1Norm(0,0);
	for (unsigned int i = 1; i < cost_matrix.size(); i++){
		calculation_counter++;
		cost_matrix[i][0] = calculate1Norm(i,0); //+ cost_matrix[i-1][0];
	}
	for (unsigned int j = 1; j < cost_matrix[0].size(); j++){
		calculation_counter++;
		cost_matrix[0][j] = calculate1Norm(0,j) + cost_matrix[0][j-1] + weights[0];
	}
	for (unsigned int i = 1; i < cost_matrix.size(); i++){
		for (unsigned int j = 1; j < cost_matrix[i].size(); j++){
			vector<double> prevCosts(3,pow(2,30));
			for (int q = 0; q < 3 && q <= i; q++){
				prevCosts[q] = cost_matrix.at(i-q).at(j-1) + weights[q];
			}
			calculation_counter++;
			cost_matrix[i][j] = calculate1Norm(i,j) + *(min_element(prevCosts.begin(), prevCosts.end()));
		}
	}

	return cost_matrix[reference.size()-1][hypothesis.size()-1];
}

void TimeAlignment::resetCosts(){
	for(unsigned int i = 0; i < cost_matrix.size(); i++){
		for (unsigned int j = 0; j < cost_matrix[i].size(); j++){
			cost_matrix[i][j] = -1;
		}
	}
	//calculation_counter = 0;
}

void TimeAlignment::outputMatrix(){
	cout << "Started with matrix" << endl;
	for(unsigned int i = 0; i < cost_matrix.size(); i++){
		for (unsigned int j = 0; j < cost_matrix[i].size(); j++){
			cout << cost_matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Done with matrix" << endl;
}
