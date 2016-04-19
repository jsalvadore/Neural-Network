#include <iostream>
#include <vector>
#include "matrix.h"
using namespace std;

class vec {
	private:
		int L;
		vector<double> values;
	public:
		vec();
		vec(int N);
		vec(int N, double val);
		int const length();
		const double get(int k);
		vector<double> get_values();
		void mod(int k, double val);
		vec add(vec v);
		vec multiply(double c);
		vec multiply(matrix M);
		vec multiply_remove(matrix M);
		vec multiply_diag(vec T);
		double dot(vec v);
		matrix outer_prod(vec v);
		void assign(vec v);
		vec concat(vec v);
};