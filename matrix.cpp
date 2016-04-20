#include "matrix.h"
using namespace std;

matrix::matrix() { //default constructor
	M = 0;
	N = 0;
	values = vector<vector<double> >(0, vector<double>(0));
}

matrix::matrix(int L1, int L2) { //constructs an L1xL2 matrix of zeros
	M = L1;
	N = L2;
	values = vector<vector<double> >(L1, vector<double>(L2,0));
}

matrix::matrix(int L1, int L2, double val) { //constructs an L1xL2 matrix of a value
	M = L1;
	N = L2;
	values = vector<vector<double> > (L1, vector<double>(L2,val));
}

const int matrix::row_dim() { //row dimension accessor
	return M;
}

const int matrix::col_dim() { //column dimension accessor
	return N;
}

const double matrix::get(int i, int j) { //accesses element (i,j)
	return values[i][j];
}

vector<vector<double> > matrix::get_values() { //accesses the matrix of values
	return values;
}

void matrix::mod(int i, int j, double val) { //modify element (i,j)
	values[i][j] = val;
}

void matrix::assign(matrix A) { //Assigns a matrix to another matrix
	M = A.row_dim();
	N = A.col_dim();
	values = A.get_values();
}

matrix matrix::transpose() { //transpose a matrix
	matrix res(N,M);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			res.mod(j,i,values[i][j]);
		}
	}
	return res;
}

matrix matrix::add(matrix A) { //Add a matrix to a matrix
	matrix res(M,N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			res.mod(i,j,A.get(i,j)+values[i][j]);
		}
	}
	return res;
}

matrix matrix::multiply(double c) { //Multiply matrix by a scalar
	matrix res(M,N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			res.mod(i,j,c*values[i][j]);
		}
	}
	return res;
}

matrix matrix::multiply(matrix A) { //Multiply a matrix by a matrix
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