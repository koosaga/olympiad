// Given a 2n x 2n skew-symmetric matrix (a[i][j] == -a[j][i])
// A Pfaffian of A is defined as
// 1/(2^n * n!) * sum_{p \in S(2n)} (sgn(p) * \prod_{i \in [n]} A_{p(2i-1), p(2i)})
// Intuitively, Pfaffian is to a general perfect matching
// as what determinant is to a bipartite perfect matching.
// Source: https://github.com/yosupo06/library-checker-problems/pull/1314/files

template <typename T> T Pfaffian(vector<vector<T>> a) {
	int n = sz(a);
	T ret = 1;
	for (int i = 1; i < n; i += 2) {
		for (int j = i; j < n; j++) {
			if (a[j][i - 1] != T(0)) {
				swap(a[j], a[i]);
				for (int k = 0; k < n; k++) {
					swap(a[k][j], a[k][i]);
				}
				if (i != j)
					ret = -ret;
				break;
			}
		}
		if (a[i][i - 1] == T(0))
			return 0;
		ret *= -a[i][i - 1];
		T inv = T(1) / a[i][i - 1];
		for (int j = i + 1; j < n; j++) {
			T z = a[j][i - 1] * inv;
			for (int k = 0; k < n; k++)
				a[j][k] -= z * a[i][k];
		}
		inv = T(1) / a[i - 1][i];
		for (int j = i + 1; j < n; j++) {
			T z = a[i - 1][j] * inv;
			for (int k = 0; k < n; k++)
				a[k][j] -= z * a[k][i];
		}
	}
	return ret;
}