#include "include/TimeAlignment.h"
#include <iostream>

using namespace std;

int main(){
	string hyp_name = "material/u4/test.dat.train";
	string ref_name = "material/u4/ref.dat.train";
	vector<double> weights = {2.0,0.0,2.0};
	TimeAlignment* t = new TimeAlignment(hyp_name, ref_name, weights);
 	cout << "lol" << endl;
	cout << t->computeDistanceRec() << endl;
	cout << t->computeDistanceRecMemoi() << endl;
	cout << t->computeDistanceDP() << endl;
	return 0;
}
