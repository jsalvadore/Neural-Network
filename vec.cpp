#include "vec.h"
using namespace std;

vec::vec() {
	L = 0;
	values = vector<double>(0,0.0);
}

vec::vec(int N) {
	L = N;
	double val = 0;
	values =vector<double>(N,val);
}

vec::vec(int N, double val) {
	L = N;
	values = vector<double>(N,val);
}

const int vec::length() {
	return L;
}

const double vec::get(int k) {
	return values[k];
}

void vec::mod(int k, double val) {
	values[k] = val;
}

vec vec::add(vec v) {
	if (L != v.length()) {
		cout << "You add vectors wrong \n";
		return vec();
	} else {
		vec res(L);
		//res.vec(L);
		for (int i = 0; i < L; i++) {
			res.mod(i,values[i] + v.get(i));
		}
		return res;
	}
}

vec vec::multiply(matrix M) {
	if (L != M.col_dim()) {
		cout << "You multiply vectors wrong \n";
		return vec();
	}	else {
		vec res(M.row_dim());
		for (int i = 0; i < M.row_dim(); i++) {
			double tmp = 0;
			for (int j = 0; j < M.col_dim(); j++) {
				tmp = tmp + M.get(i,j)*values[j];
			}
			res.mod(i,tmp);
		}
		return res;
	}
} 

void vec::assign(vec v) {
	if (L != v.length()) {cout << "You assign vectors wrong";}
	else {
		for (int i = 0; i < L; i++) {
			values[i] = v.get(i);
		}
	}
}

vec vec::concat(vec v) {
	int L_new;
	L_new = L + v.length();
	vec res(L_new);
	int index = 0;
	for (int i = 0; i < L; i++) {
		res.mod(index,values[i]);
		index++;
	}
	for (int i = 0; i < v.length(); i++) {
		res.mod(index,v.get(i));
		index++;
	}
	return res;
}

void vec::print() {
	cout << "Printing Vector of length " << L << ": \n";
	if (L == 0) {cout << "empty \n";}
	else {
		for (int i = 0; i < L; i++) {
			cout << values[i] << " ";
		} 
		cout << "\n";
	}
}

void vec::print(int k) {
	if (k >= L) {cout << "Out of bounds \n";}
	else {
		cout << values[k] << " ";
	}
}

