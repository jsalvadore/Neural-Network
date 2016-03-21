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
	//Initializing variables
	int N = D.size();
	double E_in;
	double E_val;
	double E_val_min = 10000000000;
	vector<matrix> w_opt = w;
	int t_opt = 0; 
	//Initializing weights
	x_norms = compute_norms(D);
	x_norm = max_norm(x_norms);
	this -> initialize_weights(1/x_norm);
	// Initializing data structures 
	vector<vec> X = this -> make_input();
	vector<vec> S = this -> make_signal();
	vector<vec> Delta = this -> make_sensitivity();
	//Training Loop
	for (int t = 1; t <= max_iter; t++) {
		E_in = 0;
		vector<matrix> G = this -> make_gradient();
		for (int i = 0; i < D.size(); i++) {
			vec x = this -> aug_one(D[i]);
			double pred = this -> fprop(x,X,S);
			this -> bprop(X,Delta);
			E_in += pow((X[X.size()-1][0]-y[i]),2)/N;
			this -> update_gradient(X,Delta,G);
		}
			//Validation Phase
			vector<double> y_pred = this -> predict1(D_val);
			E_val = reg_error(y_pred,y_val);
			if (E_val < E_val_min) {
				w_opt = w;
				t_opt = t;
				E_val_min = E_val;
			}
			this -> update_weights(eta,G);
	}
	
}

vector<double> nnet::predict1(vector<vector<double> > &D) {
	vector<double> res;
	vector<vec> X1 = this -> make_input();
	vector<vec> S1 = this -> make_signal();
	for (int i = 0; i < D.size(); i++) {
		vec x = this -> aug_one(D[i]);
		res.push_back(this -> fprop(x,X1,S1));
	}
	return res;
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
	for (int i = 1; i < d.size(); i++) {
		vec tmp(d[i]);
		res.push_back(tmp);
	}
	return res;
}

vector<vec> nnet::make_sensitivity() {
	vector<vec> res;
	for (int i = 1; i < d.size(); i++) {
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

double nnet::fprop(vec x, vector<vec> &X, vector<vec> &S) {
	X[0] = x;
	for (int l = 0; l < n_layers; l++) {
		S[l].assign(X[l].multiply(w[l].transpose()));
		X[l+1].assign(aug_one(sig_map(S[l])));
	}
	return X[X.size()-1].get(0);
}

void nnet::bprop(vector<vec> &X, vector<vec> &Delta) {
	Delta[Delta.size()-1] = inverse_signal(X[X.size()-1]);
	for (int l = n_layers-1; l > 0; l--) {
		vec T;
		T.assign(inverse_signal(X[l]));
		Delta[l-1].assign(Delta[l].multiply_remove(w[l]).multiply_diag(T));
	}
}

void nnet::update_gradient(vector<vec> &X, vector<vec> &Delta, vector<matrix> &G,
													 int y, int N) {
	for (int l = 0; l <= n_layers; l++) {
		G[l].assign(Delta[l].multiply(X[l]).multiply(2*(X[X.size()-1].get(0)-y)/N));
	}
}

void nnet::update_weights(double eta, vector<matrix> &G) {
	for (int l = 0; l <= n_layers; l++) {
		w[l].assign(w[l].add(G[l].multiply(-eta)));
	}
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
	vec arg(x.size());
	for (int i = 0; i < x.size(); i++) {
		arg.mod(i,x[i]);
	}
	return one.concat(arg);
}

vector<double> sig_map(vec s) {
	vector<double> res;
	for (int i = 0; i < s.length(); i++) {
		res.push_back(tanh(s.get(i)));
	}
	return res;
}

vec inverse_signal(vec x) {
	if (x.length() == 1) {
		vec res(1,x.get(0));
		return res;
	} else {
		vec res(x.length()-1);
		for (int i = 0; i < x.length(); i++) {
			res.mod(i,(1-pow(x.get(i),2)));
		}
		return res;
	}
}

double reg_error(vector<double> y_pred, vector<int> y) {
	if (y_pred.size() == y_size()) {
		double E = 0;
		for (int i = 0; i < y.size(); i++) {
			E += pow((y_pred[i]-y[i]),2);
		}
		E = E/y.size();
		return E;
	}
	else {return -1;}
}