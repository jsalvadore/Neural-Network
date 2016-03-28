#include "nnet.h"
using namespace std;

//Public Interface
nnet::nnet() {
	L = 0;
	d = vector<int>(0);
	w = vector<matrix>(0);
}

nnet::nnet(vector<int> arch) {
	L = arch.size()-1;
	d = arch;
	w = vector<matrix>(L);
	for (int i = 1; i < L+1; i++) {
		matrix W(d[i-1]+1,d[i],0);
		w[i-1] = W;
	}
}

nnet::nnet(vector<int> arch, vector<matrix> W) {
	L = arch.size()-1;
	d = arch;
	w = vector<matrix>(L);
	for (int i = 0; i < L; i++) {
		w[i] = W[i];
	}
}

const int nnet::size() {
	return L-1;
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
								 vector<int> &y_val, double eta, double alpha, double beta, int max_iter) {
	//Initializing variables
	int N = D.size();
	double E_in;
	double E_in_min = 100000000000000;
	double E_val;
	double E_val_min = 100000000000000;
	vector<matrix> w_opt = w;
	int t_opt = 0; 
	//Initializing weights
	//vector<double> x_norms = compute_norms(D);
	//double x_norm = max_norm(x_norms);
	this -> initialize_weights(.5);
	// Initializing data structures 
	vector<vec> X = this -> make_input();
	vector<vec> S = this -> make_signal();
	vector<vec> Delta = this -> make_sensitivity();
	vector<matrix> G = this -> make_gradient();
	vec x;
	//Training Loop
	int t  = 1;
	while (t <= max_iter) {
		E_in = 0;
		this -> clear_gradient(G); 
		for (int i = 0; i < D.size(); i++) {
			x.assign(aug_one(D[i]));
			double pred = this -> fprop(x,X,S);
			this -> bprop(X,Delta);
			E_in += pow((pred-y[i]),2)/N;
			this -> update_gradient(X,Delta,G,y[i],N);
		}
		if (E_in < E_in_min) {
			E_in_min = E_in; 
			eta = alpha*eta;
			this -> update_weights(eta,G);
			//Validation Phase
			vector<double> y_pred = this -> predict1(D_val,X,S);
			E_val = reg_error(y_pred,y_val);
			if (E_val < E_val_min) {
				w_opt = w;
				t_opt = t;
				E_val_min = E_val;
			}
			t++;
			cout << "E_in: " << E_in << endl;
			cout << "E_val : " << E_val << endl;
		} else {
			eta = beta*eta;
			cout << "No improvement, adjusting learning rate to " << eta << endl;
		}
	}
	cout << "Optimal Validation error is: " << E_val_min << endl; 
}

vector<double> nnet::predict1(vector<vector<double> > &D, vector<vec> &X, vector<vec> &S) {
	vector<double> res(D.size());
	for (int i = 0; i < D.size(); i++) {
		vec x;
		x.assign(aug_one(D[i]));
		res[i] = this -> fprop(x,X,S);
	}
	return res;
}

void nnet::print() {
	if (L > 0) {
		cout << "Printing a nnet with " << L-1 << " hidden units" << endl;
		cout << "The architecture is: " << endl;
		for (int i = 0; i < L; i++) {
			cout << d[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < L; i++) {
			cout << "Layer " << i+1 << ":" << endl;
			w[i].print();
		}
	} else {
		cout << "The network is empty" << endl;
	}
}

//Private Interface

void nnet::initialize_weights(double sigma) {
	default_random_engine generator;
	normal_distribution<double> distribution(0,sigma);
	for (int k = 0; k < L; k++) {
		matrix A(d[k]+1,d[k+1]);
		for (int i = 0 ; i < d[k]+1; i++) {
			for (int j = 0; j < d[k+1]; j++) {
				A.mod(i,j,distribution(generator));
			}
		}
		w[k].assign(A);
	}
}

vector<vec> nnet::make_input() {
	vector<vec> res(L+1);
	for (int i = 0; i <= L; i++) {
		vec tmp(d[i]+1);
		res[i].assign(tmp);
	}
	return res;
}

vector<vec> nnet::make_signal() {
	vector<vec> res(L);
	for (int i = 1; i <= L; i++) {
		vec tmp(d[i]);
		res[i-1].assign(tmp);
	}
	return res;
}

vector<vec> nnet::make_sensitivity() {
	vector<vec> res(L);
	for (int i = 1; i <= L; i++) {
		vec tmp(d[i]);
		res[i-1].assign(tmp);
	}
	return res;
}

vector<matrix> nnet::make_gradient() {
	vector<matrix> res(L);
	for (int i = 0; i < L; i++) {
		res[i].assign(w[i].multiply(0));
	}
	return res;
}

void nnet::clear_gradient(vector<matrix> &G) {
	for (int k = 0; k < G.size(); k++) {
		for (int i = 0; i < G[k].row_dim(); i++) {
			for (int j = 0; j < G[k].col_dim(); j++) {
				G[k].mod(i,j,0);
			}
		}
	}
}



double nnet::fprop(vec x, vector<vec> &X, vector<vec> &S) {
	X[0].assign(x);
	for (int l = 0; l < L; l++) {
		S[l].assign(X[l].multiply(w[l].transpose()));
		X[l+1].assign(aug_one(sig_map(S[l])));
	}
	return X[L].get(1);
}

void nnet::bprop(vector<vec> &X, vector<vec> &Delta) {
	Delta[L-1].assign(inverse_signal(X[L])); //This is problematic
	for (int l = L-2; l >= 0; l--) {
		vec T;
		T.assign(inverse_signal(X[l+1]));
		Delta[l].assign(Delta[l+1].multiply_remove(w[l+1]).multiply_diag(T));
	}
}

void nnet::update_gradient(vector<vec> &X, vector<vec> &Delta, vector<matrix> &G,
													 int y, int N) {
	matrix G_up;
	for (int l = 0; l < L; l++) {
		G_up.assign(Delta[l].outer_prod(X[l]).multiply(2*(X[L].get(1)-y)/N));
		G[l].assign(G[l].add(G_up));
	}
}

void nnet::update_weights(double eta, vector<matrix> &G) {
	for (int l = 0; l < L; l++) {
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
					break;
				}
		}
		res.push_back(row);
	}
	file.close();
	return res;
}

vector<int> read_response(string file_name) {
	ifstream file(file_name.c_str());
	vector<int> res;
	while(file.is_open() && !file.eof()) {
		string entry;
		getline(file,entry);
		int num = atof(entry.c_str());
		res.push_back(num);
	}
	file.close();
	return res;
}

vector<double> compute_norms(vector<vector<double> > D) {
	vector<double> res;
	for (int i = 0; i < D.size(); i++) {
		double tmp = 0;
		for (int j = 0; j < D[i].size(); j++) {
			tmp += pow(D[i][j],2);
		}
		res.push_back(sqrt(tmp));
	}
}

double max_norm(vector<double> x) {
	vector<double>::const_iterator p = x.begin();
	vector<double>::const_iterator q = x.end();
	return *max_element(p,q);
}

vec aug_one(vector<double> v) {
	vec one(1,1);
	vec arg(v.size());
	for (int i = 0; i < v.size(); i++) {
		arg.mod(i,v[i]);
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
	vec res(x.length()-1);
	for (int i = 1; i < x.length(); i++) {
		res.mod(i-1,(1-pow(x.get(i),2)));
	}
	return res;
}

double reg_error(vector<double> y_pred, vector<int> y) {
	if (y_pred.size() == y.size()) {
		double E = 0;
		for (int i = 0; i < y.size(); i++) {
			E += pow((y_pred[i]-y[i]),2);
		}
		E = E/y.size();
		return E;
	}
	else {return 100000000000000000;}
}