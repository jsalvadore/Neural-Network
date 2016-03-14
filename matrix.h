#include<iostream>
#include<vector>
using namespace std; 

class matrix {
	private:
		int M;
		int N;
		vector<vector<double> > values;
	public:
		matrix();
		matrix(int L1, int L2);
		matrix(int L1, int L2, double val);
		const int  col_dim();
		const int row_dim();
		double const get(int i, int j);
		void mod(int i, int j, double val);
		void assign(matrix A);
		matrix transpose();
		void print();
};
