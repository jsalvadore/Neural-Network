#include "matrix.h"
using namespace std;

matrix::matrix() {
	M = 0;
	N = 0;
	values = vector<vector<double> >(0, vector<double>(0));
}

matrix::matrix(int L1, int L2) {
	M = L1;
	N = L2;
	values = vector<vector<double> >(L1, vector<double>(L2,0));
}

matrix::matrix(int L1, int L2, double val) {
	M = L1;
	N = L2;
	values = vector<vector<double> > (L1, vector<double>(L2,val));
}

const int matrix::col_dim() {
	return M;
}

const int matrix::row_dim() {
	return N;
}

const double matrix::get(int i, int j) {
	return values[i][j];
}

void matrix::mod(int i, int j, double val) {
	values[i][j] = val;
}

void matrix::assign(matrix A) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			values[i][j] = A.get(i,j);
		}
	}
}

matrix matrix::transpose() {
	matrix res(N,M);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			res.mod(j,i,values[i][j]);
		}
	}
	return res;
}

void matrix::print() {
	cout << "Printing Matrix: \n";
	if (M == 0 || N == 0) {cout << "empty \n";}
	else {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (j == N-1) {
					cout << values[i][j] << "\n";
				} else {
					cout << values[i][j] << " ";
				}
			}
		}
	}
}