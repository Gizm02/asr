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
	cost_matrix.resize(hypothesis.size(), buffer);

	for (vector< vector<double> >::iterator it = cost_matrix.begin(); it != cost_matrix.end(); it++){
		it->resize(reference.size(), -1.0);
	}
	
	pair<int, int> pairBuffer(0,0);
	vector<pair<int,int> > pairVectorBuffer;
	backtrack_matrix.resize(hypothesis.size(), pairVectorBuffer);
	for (vector< vector<pair<int,int> > >::iterator it = backtrack_matrix.begin(); it != backtrack_matrix.end(); it++){
		it->resize(reference.size(), pairBuffer);
	}


}
double TimeAlignment::calculate1Norm(int xPos, int yPos){
	return abs(hypothesis.at(xPos) - reference.at(yPos));
}
double TimeAlignment::computeDistanceRec(){
	return computeDistanceRec(hypothesis.size() -1, reference.size() -1);
}
double TimeAlignment::computeDistanceRec(int xPos, int yPos){
	vector<double> prevCosts(3,pow(2,30));
	if (xPos == 0 ){
		return calculate1Norm(0, yPos);
	} else if(yPos == 1){
		prevCosts.at(0) = computeDistanceRec(xPos -1, yPos -0) + weights[0];
		prevCosts.at(1) = computeDistanceRec(xPos -1, yPos -1) + weights[1];
		return calculate1Norm(xPos, yPos) + *(min_element(prevCosts.begin(), prevCosts.end()));
	} else if(yPos == 0){
		return calculate1Norm(xPos-1, 0) + computeDistanceRec(xPos -1, 0) + weights[0];
	} else {
		prevCosts.at(0) = computeDistanceRec(xPos -1, yPos -0) + weights[0];
		prevCosts.at(1) = computeDistanceRec(xPos -1, yPos -1) + weights[1];
		prevCosts.at(2) = computeDistanceRec(xPos -1, yPos -2) + weights[2];
		return calculate1Norm(xPos, yPos) + *(min_element(prevCosts.begin(), prevCosts.end()));
	}
}
double TimeAlignment::computeDistanceRecMemoi(){
	return computeDistanceRecMemoi(hypothesis.size() -1, reference.size() -1);
}
double TimeAlignment::computeDistanceRecMemoi(int xPos, int yPos){
	vector<double> prevCosts(3,pow(2,30));
	if (xPos == 0 ){
		return calculate1Norm(0, yPos);
	} else if(yPos == 1){
		if (cost_matrix.at(xPos-1).at(yPos-0) == -1){
			cost_matrix[xPos-1][yPos-0] = computeDistanceRecMemoi(xPos -1, yPos - 0);
		}
		prevCosts.at(0) = cost_matrix[xPos-1][yPos-0] + weights[0];
		if (cost_matrix.at(xPos-1).at(yPos-1) == -1){
			cost_matrix[xPos-1][yPos-1] = computeDistanceRecMemoi(xPos -1, yPos -1);
		}
		prevCosts.at(1) = cost_matrix[xPos-1][yPos-1] + weights[1];
		return calculate1Norm(xPos, yPos) + *(min_element(prevCosts.begin(), prevCosts.end()));
	} else if(yPos == 0){
		if (cost_matrix.at(xPos-1).at(yPos-0) == -1){
			cost_matrix[xPos-1][yPos-0] = computeDistanceRecMemoi(xPos -1, yPos - 0);
		}
		prevCosts.at(0) = cost_matrix[xPos-1][yPos-0] + weights[0];
		return calculate1Norm(xPos-1, 0) + prevCosts.at(0);
	} else {
		if (cost_matrix.at(xPos-1).at(yPos-0) == -1){
			cost_matrix[xPos-1][yPos-0] = computeDistanceRecMemoi(xPos -1, yPos - 0);
		}
		prevCosts.at(0) = cost_matrix[xPos-1][yPos-0] + weights[0];
		if (cost_matrix.at(xPos-1).at(yPos-1) == -1){
			cost_matrix[xPos-1][yPos-1] = computeDistanceRecMemoi(xPos -1, yPos -1);
		}
		prevCosts.at(1) = cost_matrix[xPos-1][yPos-1] + weights[1];
		if (cost_matrix.at(xPos-1).at(yPos-2) == -1){
			cost_matrix[xPos-1][yPos-2] = computeDistanceRecMemoi(xPos -1, yPos -2);
		} 
		prevCosts.at(2) = cost_matrix[xPos-1][yPos-2] + weights[2];
		return calculate1Norm(xPos, yPos) + *(min_element(prevCosts.begin(), prevCosts.end()));
	}
}
double TimeAlignment::computeDistanceDP(){
	cost_matrix[0][0] = calculate1Norm(0,0);
	for (int i = 1; i < (int) cost_matrix.size(); i++){
		cost_matrix[i][0] = calculate1Norm(i,0) + cost_matrix[i-1][0];
	}
	for (int j = 1; j < (int)cost_matrix[0].size(); j++){
		cost_matrix[0][j] = calculate1Norm(0,j) + cost_matrix[0][j-1];
	}

	for (int i = 1; i < (int)cost_matrix.size(); i++){
		for (int j = 1; j <(int) cost_matrix[0].size(); j++){
			vector<double> prevCosts(3,pow(2,30));
			for (int q = 0; q < 3; q++){
				if (j == 1 && q == 2){
					break;
				}
				prevCosts[q] = cost_matrix.at(i-1).at(j-q) + weights[q];
			}
			cost_matrix[i][j] = calculate1Norm(i,j) + *(min_element(prevCosts.begin(), prevCosts.end()));
		}
	}

	return cost_matrix[hypothesis.size() -1][ reference.size() -1];
}
