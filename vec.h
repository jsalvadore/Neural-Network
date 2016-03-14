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
		void mod(int k, double val);
		vec add(vec v);
		vec multiply(matrix M);
		void assign(vec v);
		vec concat(vec v);
		void print();
		void print(int k);
}; 