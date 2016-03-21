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
		const int row_dim();
		const int  col_dim();
		double const get(int i, int j);
		vector<vector<double> > get_values();
		void mod(int i, int j, double val);
		void assign(matrix A);
		matrix transpose();
		matrix add(matrix A);
		matrix multiply(double c);
		matrix multiply(matrix A);
		void print();
};
