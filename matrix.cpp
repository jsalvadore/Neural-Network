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

const int matrix::row_dim() {
	return M;
}

const int matrix::col_dim() {
	return N;
}

const double matrix::get(int i, int j) {
	return values[i][j];
}

vector<vector<double> > matrix::get_values() {
	return values;
}

void matrix::mod(int i, int j, double val) {
	values[i][j] = val;
}

void matrix::assign(matrix A) {
	M = A.row_dim();
	N = A.col_dim();
	values = A.get_values();
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

matrix matrix::add(matrix A) {
	matrix res(M,N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			res.mod(i,j,A.get(i,j)+values[i][j]);
		}
	}
	return res;
}

matrix matrix::multiply(double c) {
	matrix res(M,N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			res.mod(i,j,c*values[i][j]);
		}
	}
	return res;
}

matrix matrix::multiply(matrix A) {
	matrix res(A.row_dim(),N);
	for (int i = 0; i < A.row_dim(); i++) {
		for (int j = 0; j < N; j++) {
			double tmp = 0;
			for (int k = 0; k < M; k++) {
				tmp += A.get(i,k)*values[k][j];
			}
			res.mod(i,j,tmp);
		}
	}
	return res;
}