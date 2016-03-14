#include "vec.h"
#include "matrix.h"

class nnet {
	private:
		int n_layers;
		vector<int> d;
		vector<matrix> w;
	public: 
		nnet(vector<int> arch);
		nnet(vector<int> arch, vector<matrix> W);
		const matrix get_weights(int k);
		mod_weights(int k, matrix A);
		train(vector<vector<double>> D, vector<int> y, vector<vector<double>> D_val, 
					vector<int> y_val, double eta, int max_iter);
		predict(vector<vector<double>> D_test, vector<int> y_test);
};

void nnet::nnet(vector<int> arch) {
	d = arch;
	n_layers = arch.length();
}

void nnet::nnet(vector<int> arch, vector<matrix> W) {
	d = arch;
	n_layers = arch.length();
	for (int i = 0; i < n_layers; i++) {
		w[i].assign(W[i]);
	}
}

const matrix nnet::get_weights(int k) {
	return w[k];
}

void nnet::mod_weights(int k, matrix A) {
	w[k].assign(A);
}

void nnet::train(vector<vector<double>> D, vector<int> y, vector<vector<double>> D_val,
								 vector<int> y_val, double eta, int max_iter) {
	
	
}

vector<int> nnet::predict(vector<vector<double>> D_test, vector<int> y_test)