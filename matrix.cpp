#include "matrix.h"
using namespace std;

matrix::matrix() {
	M = 0;
	N = 0;
}

matrix::matrix(int L1, int L2) {
	M = L1;
	N = L2;
}

matrix::matrix(int L1, int L2, double val) {
	M = L1;
	N = L2;
	for (int i = 0; i < L1; i++) {
		for (int j = 0; j < L2; j++) {
			values[i][j] = val;
		}
	}
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

const void matrix::print() {
	cout << "Printing Matrix: \n";
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (j = N-1) {
				cout << values[i][j] << "\n";
			} else {
				cout << values[i][j] << " ";
			}
		}
	}
}