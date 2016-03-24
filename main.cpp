//The following is a program to read in training, validation, and test sets and their labels
//and train a neural network and evaluate its performance on these data. 

#include "nnet.h"
using namespace std;
		
int main() {
	//Data Set Parameters
	string name = "D.csv";
	string name_y = "y.csv";
	string name_val = "D_val.csv";
	string name_y_val = "y_val.csv";
	string name_test = "D_test.csv";
	string name_y_test = "y_test.csv";
	int L = 1;
	int dim_data = 14;
	int n_train = 5992;
	int n_val = 1498;
	int n_test = 7490;
	//nnet Parameters
	int arch_size = L=2;
	vector<int> d;
	d.push_back(dim_data);
	d.push_back(10);
	d.push_back(1);
	double eta = 1;
	int max_iter = 1;

	//First read in the data files
	vector<vector<double> > D = read_csv(name,dim_data);
	vector<int> y = read_response(name_y);
	vector<vector<double> > D_val = read_csv(name_val,dim_data);
	vector<int> y_val = read_response(name_y_val);
	vector<vector<double> > D_test = read_csv(name_test,dim_data);
	vector<int> y_test = read_response(name_y_test);
	//Relabeling
	y = relabel(y);
	y_val = relabel(y_val);
	y_test = relabel(y_test); 
		
	//Initialize the network
	nnet network(d);
	network.print();
	network.train(D,y,D_val,y_val,eta,max_iter);
	network.print();

	
	return 0;
}