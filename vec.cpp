#include "vec.h"
using namespace std;

vec::vec() { //Default Constructor
	L = 0;
	values = vector<double>(0,0.0);
}

vec::vec(int N) { //Constructs a zero vector of size N
	L = N;
	double val = 0;
	values =vector<double>(N,val);
}

vec::vec(int N, double val) { //Constructs an vector of size N all of a single value
	L = N;
	values = vector<double>(N,val);
}

const int vec::length() { //Size accessor
	return L;
}

const double vec::get(int k) { //Vector element accessor
	return values[k];
}

vector<double> vec::get_values() { //Returns the whole vector of values
	return values;
}

void vec::mod(int k, double val) { //Modifies an element
	values[k] = val;
}

vec vec::add(vec v) { //Adds two vectors 
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

vec vec::multiply(double c) { //Multiplies a vector by a scalar
	vec res(L);
	for (int i = 0; i < L; i++) {
		res.mod(i,c*values[i]);
	}
	return res;
}

vec vec::multiply(matrix M) { //Multiplies a vector by a matrix
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

vec vec::multiply_remove(matrix M) { 
	//Multiplies a vector by a matrix and removes the top row of the result
	vec tmp = this -> multiply(M);
	vec res(tmp.length()-1);
	for (int i = 1; i < tmp.length(); i++) {
		res.mod(i-1,tmp.get(i));
	}
	return res;
}

vec vec::multiply_diag(vec T) {
	//Multiplies a vector by a diagonal matrix represented by another vector
	vec res(L);
	for (int i = 0; i < L; i++) {
		res.mod(i,T.get(i)*values[i]);
	}
	return res;
}

double vec::dot(vec v) { //dot product between two vectors
	double res = 0;
	for (int i = 0; i < L; i++) {
		res += v.get(i)*values[i];
	}
	return res;
}

matrix vec::outer_prod(vec v) { //outer product between two vectors
	matrix res(v.length(),L);
	for (int i = 0; i < v.length(); i++) {
		for (int j = 0; j < L; j++) {
			res.mod(i,j,v.get(i)*values[j]);
		}
	}
	return res;
}

void vec::assign(vec v) { //Assignment operator
	L = v.length();
	values = v.get_values();
}

vec vec::concat(vec v) { 
	//Concatenates two vectors, adding the argument to the right
	//of the current vector
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

