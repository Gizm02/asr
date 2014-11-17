#include "include/TimeAlignment.h"

int main(){
	string hyp_name = "materials/u4/test.dat";
	string ref_name = "materials/u4/ref.dat";
	vector<double> weights = {2.0,0.0,2.0};

	TimeAlignment t(hyp_name, ref_name, weights);
 
	return 0;
}
