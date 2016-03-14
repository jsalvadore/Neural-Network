class matrix {
	private:
		int M;
		int N;
		vector<vector<double>> values;
	public:
		matrix(int L1, int L2);
		matrix(int L1, int L2, double val);
		const col_dim();
		const row_dim();
		const get(int i, int j);
		mod(int i, int j, double val);
		transpose();
};

void matrix::matrix(int L1, int L2) {
	M = L1;
	N = L2;
}

void matrix::matrix(int L1, int L2, double val) {
	M = L1;
	N = L2;
	for (int i = 0; i < L1; i++) {
		for (int j = 0; j < L2; j++) {
			values[i][j] = val;
		}
	}
}

int matrix::col_dim() {
	return M;
}

int matrix::row_dim() {
	return N;
}

double matrix::get(int i, int j) {
	return values[i][j];
}

void matrix::mod(int i, int j, double val) {
	values[i][j] = val;
}

matrix matrix::transpose() {
	matrix res(N,M);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			res[j][i] = values[i][j];
		}
	}
	return res;
}