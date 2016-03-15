#include "vec.h"
#include <vector>
using namespace std;

class nnet {
	private:
		int n_layers;
		vector<int> d;
		vector<matrix> w;
	public: 
		nnet();
		nnet(vector<int> arch);
		nnet(vector<int> arch, vector<matrix> W);
		const int size();
		const int dim(int k);
		matrix get_weights(int k);
		void mod_weights(int k, matrix A);
		void train(vector<vector<double> > D, vector<int> y, vector<vector<double> > D_val, 
					vector<int> y_val, double eta, int max_iter);
		vector<int> predict(vector<vector<double> > D_test, vector<int> y_test);
		void print();
};
