#include "nnet.h"
using namespace std;

nnet::nnet(vector<int> arch) {
	d = arch;
	n_layers = arch.size();
}

nnet::nnet(vector<int> arch, vector<matrix> W) {
	d = arch;
	n_layers = arch.size();
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

void nnet::train(vector<vector<double> > D, vector<int> y, vector<vector<double> > D_val,
								 vector<int> y_val, double eta, int max_iter) {
	
	
}

vector<int> nnet::predict(vector<vector<double> > D_test, vector<int> y_test) {
	
}