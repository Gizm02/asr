#include <string>
#include <vector> 
#include <utility> 


using namespace std;

class TimeAlignment{
	public:
		TimeAlignment(string hypo_filename, string ref_filename, vector<double> w);
		double computeDistanceRec();		
		double computeDistanceRecMemoi();
		void computeDistanceDP();
	private:
		vector<double> reference;
		vector<double> hypothesis;
		vector<vector<double> > cost_matrix;
		vector<vector<pair<int,int> > > backtrack_matrix;
		vector<double> weights;
		
		int calculation_counter;
		double calculate1Norm(int xPos, int yPos);
		double computeDistanceRec(int xPos, int yPos);
		double computeDistanceRecMemoi(int xPos, int yPos);
};
