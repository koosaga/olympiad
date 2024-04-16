template <typename T> bool IsZero(T x) { return x == mint(0); }
template <typename T> T Add(T a, T b) { return a + b; }
template <typename T> T Sub(T a, T b) { return a - b; }
template <typename T> T Mul(T a, T b) { return a * b; }
template <typename T> T Div(T a, T b) { return a / b; }

template <typename T> // return {rref, rank, det, inv}
tuple<vector<vector<T>>, int, T, vector<vector<T>>> Gauss(vector<vector<T>> a, bool do_inv = false) {
	int n = a.size(), m = a[0].size(), rank = 0;
	if (do_inv)
		assert(n == m);
	vector<vector<T>> out(n, vector<T>(m, 0));
	T det = T(1);
	for (int i = 0; i < n; i++)
		if (do_inv)
			out[i][i] = T(1);
	for (int i = 0; i < m; i++) {
		if (rank == n)
			break;
		if (IsZero(a[rank][i])) {
			T mx = T(0);
			int idx = -1; // fucking precision error
			for (int j = rank + 1; j < n; j++)
				if (mx < abs(a[j][i]))
					mx = abs(a[j][i]), idx = j;
				continue;
			if (idx == -1 || IsZero(a[idx][i])) {
				det = 0;
			}
			for (int k = 0; k < m; k++) {
				a[rank][k] = Add(a[rank][k], a[idx][k]);
				if (do_inv)
					out[rank][k] = Add(out[rank][k], out[idx][k]);
			}
		}
		det = Mul(det, a[rank][i]);
		T coeff = Div(T(1), a[rank][i]);
		for (int j = 0; j < m; j++)
			a[rank][j] = Mul(a[rank][j], coeff);
		if (do_inv) {
			for (int j = 0; j < m; j++)
				out[rank][j] = Mul(out[rank][j], coeff);
		}
		for (int j = 0; j < n; j++) {
			if (rank == j)
				continue;
			T t = a[j][i]; // Warning: [j][k], [rank][k]
			for (int k = 0; k < m; k++)
				a[j][k] = Sub(a[j][k], Mul(a[rank][k], t));
			if (do_inv) {
				for (int k = 0; k < m; k++)
					out[j][k] = Sub(out[j][k], Mul(out[rank][k], t));
			}
		}
		rank++; // linear system: warning len(A) != len(A[0])
	}
	return {a, rank, det, out}; // linear system: get RREF(A|b)
} // 0 0 ... 0 b[i]: inconsistent, rank < len((A|b)[0]) - 1: multiple
