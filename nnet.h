#include "vec.h"
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>

using namespace std;

//Helper Functions
vector<vector<double> > read_csv(string file_name, int dim_data);
vector<int> read_response(string file_name);
vector<double> compute_norms(vector<vector<double> > &D);
double max_norm(vector<double> &x);
vec aug_one(vector<double> x);
vector<double> sig_map(vec s);
vec inverse_signal(vec x);
double reg_error(vector<double> y_pred, vector<int> y);
int sgn(double num);

class nnet {
	private:
		int L;
		vector<int> d;
		vector<matrix> w;
		void initialize_weights(double sigma);
		vector<vec> make_input();
		vector<vec> make_signal();
		vector<vec> make_sensitivity();
		vector<matrix> make_gradient();
		void clear_gradient(vector<matrix> &G);
		double fprop(vec x, vector<vec> &X, vector<vec> &S);
		void bprop(vector<vec> &X, vector<vec> &Delta);
		vector<double> predict1(vector<vector<double> > &D, vector<vec> &X, vector<vec> &S);
		void update_gradient(vector<vec> &X, vector<vec> &Delta, vector<matrix> &G, 
												 vector<matrix> &G_up, int y, int N);
		void update_weights(double eta, vector<matrix> &G);
	public: 
		nnet();
		nnet(vector<int> arch);
		nnet(vector<int> arch, vector<matrix> W);
		const int size();
		const vector<int> arch();
		const int dim(int k);
		matrix get_weights(int k);
		void mod_weights(int k, matrix A);
		void train(vector<vector<double> > &D, vector<int> &y, vector<vector<double> > &D_val, 
					vector<int> &y_val, double eta, int max_iter);
		vector<int> predict(vector<vector<double> > &D_test);
};
