class vec {
	private:
		int L;
		double values[L];
	public:
		vec(const int N);
		vec(const int N, const double val);
		const length();
		const get(const int k);
		mod(const int k, const double val);
		add(const vec v);
		multiply(const matrix M);
		assign(vec v);
		concat(const vec v1, const vec v2);
}; 

void vec::vec(const int L) {
	L = N;
}

void vec::vec(const int L, const double val) {
	L = N;
	for (int i = 0; i < L; i++) {
		values[i] = val;
	}
}

const int vec::length() {
	return L;
}

const double vec::get(const int k) {
	return values[k];
}

void mod(const int k, const double val) {
	values[k] = val;
}

vec vec::add(const vec v) {
	if (vec.L != v.length()) {break;}
	else {
		vec res(L);
		for (int i = 0; i < L; i++) {
			res[i] = values[i] + v.get(i);
		}
	}
	return res;
}

vec vec::multiply(const matrix M) {
	if (L != M.col_dim()) {break;}
	else {
		vec res(M.row_dim());
		for (int i = 0; i < M.row_dim(); i++) {
			double tmp = 0;
			for (int j = 0; j < M.col_dim(); j++) {
				tmp = tmp + M.get(i,j)*values[j];
			}
		}
		return res;
	}
}

void vec::assign(vec v) {
	if (L != v.length()) {break;}
	else {
		for (int i = 0; i < L; i++) {
			values[i] = v.get(i);
		}
	}
}

vec vec::concat(const vec v1, const vec v2) {
	L_new = v1.length() + v2.length();
	vec res(L_new);
	int index = 0;
	for (int i = 0; i < v1.length(); i++) {
		res.mod(index,v1.get(i));
		index++;
	}
	for (int i = 0; i < v2.length(); i++) {
		res.mod(index,v2.get(i));
		index++;
	}
	return res;
}

