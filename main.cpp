//The following is a program to read in training, validation, and test sets and their labels
//and train a neural network and evaluate its performance on these data. 

#include "nnet.h"
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

vector<vector<double> > read_csv(string file_name);
vector<double> read_response(string file_name);

vector<vector<double> > read_csv(string file_name) {
	ifstream file(file_name.c_str());
	vector<vector<double> > res;
	while (file.is_open() && !file.eof()) {
		vector<double> row;
		int start = 0;
		int end = 0;
		int count = 0;
		string line;
		getline(file,line);
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ',') {
				end = i;
				string tmp;
				for (int j = start; j < end; j++) {
					tmp.push_back(line[j]);
				}
				double num = atof(tmp.c_str());
				row.push_back(num);
				start = i+1;
				count++;
			}
				if (count == 13) {
					string tmp;
					for (int j = start; j < line.size(); j++) {
						tmp.push_back(line[j]);
					}
					double num = atof(tmp.c_str());
					row.push_back(num);
				}
		}
		res.push_back(row);
	}
	file.close();
	return res;
}

vector<double> read_response(string file_name) {
	ifstream file(file_name.c_str());
	vector<double> res;
	while(file.is_open() && !file.eof()) {
		string entry;
		getline(file,entry);
		double num = atof(entry.c_str());
		res.push_back(num);
	}
	file.close();
	return res;
}
		
		
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
	vector<vector<double> > D = read_csv(name);
	vector<double> y = read_response(name_y);
	vector<vector<double> > D_val = read_csv(name_val);
	vector<double> y_val = read_response(name_y_val);
	vector<vector<double> > D_test = read_csv(name_test);
	vector<double> y_test = read_response(name_y_test);
	
	
	return 0;
}