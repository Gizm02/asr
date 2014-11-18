#include "include/TimeAlignment.h"
#include <iostream>

using namespace std;

int main(){
	string hyp_name = "material/u4/test.dat";
	string ref_name = "material/u4/ref.dat";
	vector<double> weights = {2.0, 0.0, 2.0};
	TimeAlignment* t = new TimeAlignment(hyp_name, ref_name, weights);

	cout << "Recursion formula: " << t->computeDistanceRec() << " Calc. count: " << t->calculation_counter << endl;	
	t->resetCosts();
	cout << "Recursion formula with memoization: " << t->computeDistanceRecMemoi() << " Calc. count: " << t->calculation_counter << endl;
	t->resetCosts();
	cout << "Dynamic programming formula: " << t->computeDistanceDP() << " Calc. count: " << t->calculation_counter << endl;

	return 0;
}
