#include "nnet.h"
using namespace std;

//Public Interface
nnet::nnet() {
	n_layers = 0;
	d = vector<int>(0);
	w = vector<matrix>(0);
}

nnet::nnet(vector<int> arch) {
	n_layers = arch.size()-1;
	d = arch;
	w = vector<matrix>(n_layers);
	for (int i = 1; i < n_layers+1; i++) {
		matrix W(d[i-1]+1,d[i],0);
		w[i-1] = W;
	}
}

nnet::nnet(vector<int> arch, vector<matrix> W) {
	n_layers = arch.size()-1;
	d = arch;
	w = vector<matrix>(n_layers);
	for (int i = 0; i < n_layers; i++) {
		w[i] = W[i];
	}
}

const int nnet::size() {
	return n_layers;
}

const vector<int> nnet::arch() {
	return d;
}

const int nnet::dim(int k) {
	return d[k];
}

matrix nnet::get_weights(int k) {
	return w[k];
}

void nnet::mod_weights(int k, matrix A) {
	w[k].assign(A);
}

void nnet::train(vector<vector<double> > &D, vector<int> &y, vector<vector<double> > &D_val,
								 vector<int> &y_val, double eta, int max_iter) {
	double E_in = 0;
	double E_val = 0;
	double E_val_min = 0;
	int iter_opt = 0; 
	vector<matrix> w_opt;
	x_norms = compute_norms(D);
	x_norm = max_norm(x_norms);
	this -> initialize_weights(1/x_norm);
	vector<vec> x = this -> make_input();
	vector<vec> s = this -> make_signal();
	vector<vec> delta = this -> make_sensitivity();
	vector<matrix> G = this -> make_gradient();
	
	
}

vector<int> nnet::predict(vector<vector<double> > &D_test, vector<int> &y_test) {
	
}

void nnet::print() {
	if (n_layers > 0) {
		cout << "Printing a nnet with " << n_layers << " hidden units" << endl;
		cout << "The architecture is: " << endl;
		for (int i = 0; i < n_layers; i++) {
			cout << d[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < n_layers; i++) {
			cout << "Layer " << i+1 << ":" << endl;
			w[i].print();
		}
	} else {
		cout << "The network is empty" << endl;
	}
}

//Private Interface

vector<vec> nnet::make_input() {
	vector<vec> res;
	for (int i = 0; i < d.size(); i++) {
		vec tmp(d[i]+1);
		res.push_back(tmp);
	}
	return res;
}

vector<vec> nnet::make_signal() {
	vector<vec> res;
	for (int i = 0; i < d.size(); i++) {
		vec tmp(d[i]);
		res.push_back(tmp);
	}
	return res;
}

vector<vec> nnet::make_sensitivity() {
	vector<vec> res;
	for (int i = 0; i < d.size(); i++) {
		vec tmp(d[i]);
		res.push_back(tmp);
	}
	return res;
}

vector<matrix> nnet::make_gradient() {
	vector<matrix> res;
	for (int i = 0; i < w.size(); i++) {
		res.push_back(w.get_weights(i).multiply(0));
	}
	return res;
}

void nnet::initialize_weights(double sigma) {
	mersenne_twister_engine generator;
	normal_distribution<double> distribution(0,sigma);
	for (int k = 0; k < w.size(); k++) {
		matrix A(d[k]+1,d[k+1]);
		for (int i = 0 ; i < d[k]+1; i++) {
			for (int j = 0; j < d[k+1]; j++) {
				A.mod(i,j,distribution(generator));
			}
		}
		this -> mod_weights(k,A);
	}
}

double nnet::fprop(vec x, vector<vec> &X, vector<vec> &S, vector<matrix> &G) {
		return 0;
}

void nnet::bprop(vector<vec> &X, vector<vec> &Delta) {
	
}


//Helper Functions

vector<vector<double> > read_csv(string file_name,int dim_data) {
	ifstream file(file_name.c_str());
	vector<vector<double> > res;
	while (file.is_open() && !file.eof()) {
		vector<double> row;
		int start = 0;
		int end = 0;
		int count = 0;
		string line;
		getline(file,line);
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ',') {
				end = i;
				string tmp;
				for (int j = start; j < end; j++) {
					tmp.push_back(line[j]);
				}
				double num = atof(tmp.c_str());
				row.push_back(num);
				start = i+1;
				count++;
			}
				if (count == dim_data-1) {
					string tmp;
					for (int j = start; j < line.size(); j++) {
						tmp.push_back(line[j]);
					}
					double num = atof(tmp.c_str());
					row.push_back(num);
				}
		}
		res.push_back(row);
	}
	file.close();
	return res;
}

vector<double> read_response(string file_name) {
	ifstream file(file_name.c_str());
	vector<double> res;
	while(file.is_open() && !file.eof()) {
		string entry;
		getline(file,entry);
		double num = atof(entry.c_str());
		res.push_back(num);
	}
	file.close();
	return res;
}

vector<double> compute_norms(vector<vector<double> > &D) {
	vector res;
	for (int i = 0; i < D.size(); i++) {
		double tmp = 0;
		for (int j = 0; j < D[i].size(); i++) {
			tmp += D[i][j]*D[i][j];
		}
		res.push_back(sqrt(tmp));
	}
}

double max_norm(vector<double> x) {
	vector<double>::const_iterator p = x.begin();
	vector<double>::const_iterator q = x.end();
	return *max_element(p,q);
}

vec aug_one(vector<double> x) {
	vec one(1,1);
	return one.concat(x);
}
