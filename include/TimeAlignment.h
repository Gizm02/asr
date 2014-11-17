#include <string>
#include <vector> 
#include <utility> 


using namespace std;

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
		vector<int> weights;
		
		int calculation_counter;

};
