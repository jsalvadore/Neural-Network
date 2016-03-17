//The following is a program to read in training, validation, and test sets and their labels
//and train a neural network and evaluate its performance on these data. 

#include "nnet.h"
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
		
int main() {
	//Data Set Parameters
	string name = "D.csv";
	string name_y = "y.csv";
	string name_val = "D_val.csv";
	string name_y_val = "y_val.csv";
	string name_test = "D_test.csv";
	string name_y_test = "y_test.csv";
	int dim_data = 14;
	int n_data = 5992;
	int n_val;
	int n_test;
	//nnet Parameters
	//vector<int> d = {dim_data,10,1}
	double eta = 1.5;
	int max_iter = 100000;

	//First read in the data files
	vector<vector<double> > D = read_csv(name,dim_data);
	vector<double> y = read_response(name_y);
	vector<vector<double> > D_val = read_csv(name_val,dim_data);
	vector<double> y_val = read_response(name_y_val);
	vector<vector<double> > D_test = read_csv(name_test,dim_data);
	vector<double> y_test = read_response(name_y_test);
	
	
	return 0;
}