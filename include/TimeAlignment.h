#include <string>
#include <vector> 
#include <utility> 


using namespace std;

class TimeAlignment{
	public:
		TimeAlignment(string hypo_filename, string ref_filename, vector<double> w);
		double computeDistanceRec();		
		double computeDistanceRecMemoi();
		double computeDistanceDP();
		void resetCosts();
		void outputMatrix();
		int calculation_counter;
	private:
		vector<double> reference;
		vector<double> hypothesis;
		vector<vector<double> > cost_matrix;
		vector<vector<pair<int,int> > > backtrack_matrix;
		vector<double> weights;
		
		
		double calculate1Norm(int xPos, int yPos);
		double computeDistanceRec(int xPos, int yPos);
		double computeDistanceRecMemoi(int xPos, int yPos);
};
