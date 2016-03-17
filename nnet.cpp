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
	int count = 1;
	for (int i = 1; i < n_layers+1; i++) {
		matrix W(d[i-1]+1,d[i],0);
		W.print();
		w[i-1] = W;
		w[i-1].print();
		cout << count << endl;
		count++;
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

vector<matrix> nnet::make_grad() {
	vector<matrix> res;
	for (int i = 0; i < w.size(); i++) {
		res.push_back(w.get_weights(i).multiply(0));
	}
	return res;
}

//Helper Functions

vector<vector<double> > read_csv(string file_name) {
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
				if (count == 13) {
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
