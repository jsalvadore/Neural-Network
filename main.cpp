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
	int dim_data = 2;
	int n_train = 800;
	int n_val = 200;
	int n_test = 1000;
	//nnet Parameters
	int L = 3;
	//The architecture
	vector<int> d;
	d.push_back(dim_data);
	d.push_back(10);
	d.push_back(1);
	double eta = 1;
	int max_iter = 100;

	//First read in the data files
	vector<vector<double> > D = read_csv(name,dim_data);
	vector<int> y = read_response(name_y);
	vector<vector<double> > D_val = read_csv(name_val,dim_data);
	vector<int> y_val = read_response(name_y_val);
	vector<vector<double> > D_test = read_csv(name_test,dim_data);
	vector<int> y_test = read_response(name_y_test); 

	D.pop_back();
	y.pop_back();
	D_val.pop_back();
	y_val.pop_back();
	D_test.pop_back();
	y_test.pop_back(); 
		
	//Initialize the network
	cout << "Initializing Network" << endl;
	nnet network(d);
	//Train the Network
	cout << "Training the Network" << endl;
	network.train(D,y,D_val,y_val,eta,max_iter);
	//Prediction
	vector<int> y_pred = network.predict(D_test);
	//Compute Error
	double E_test = 0;
	for (int i = 0; i < y_test.size(); i++) {
		if (y_pred[i] != y_test[i]) {E_test++;}
	}
	E_test = E_test/n_test;
	
	cout << "The final test error is: " << E_test << endl; 

	
	return 0;
}
