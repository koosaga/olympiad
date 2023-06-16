// max cTx st Ax <= b, x >= 0

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define MP make_pair
#define ltj(X)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         \
	if (s == -1 || MP(X[j], N[j]) < MP(X[s], N[s]))                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    \
	s = j

template <typename DOUBLE> struct LPSolver {
	const DOUBLE eps = 1e-8, inf = 1 / .0;
	using vd = vector<DOUBLE>;
	using vvd = vector<vd>;
	using vi = vector<int>;
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd &A, const vd &b, const vd &c) : m(sz(b)), n(sz(c)), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
		rep(i, 0, m) rep(j, 0, n) D[i][j] = A[i][j];
		rep(i, 0, m) {
			B[i] = n + i;
			D[i][n] = -1;
			D[i][n + 1] = b[i];
		}
		rep(j, 0, n) {
			N[j] = j;
			D[m][j] = -c[j];
		}
		N[n] = -1;
		D[m + 1][n] = 1;
	}

	void pivot(int r, int s) {
		DOUBLE *a = D[r].data(), inv = 1 / a[s];
		rep(i, 0, m + 2) if (i != r && abs(D[i][s]) > eps) {
			DOUBLE *b = D[i].data(), inv2 = b[s] * inv;
			rep(j, 0, n + 2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		rep(j, 0, n + 2) if (j != s) D[r][j] *= inv;
		rep(i, 0, m + 2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for (;;) {
			int s = -1;
			rep(j, 0, n + 1) if (N[j] != -phase) ltj(D[x]);
			if (D[x][s] >= -eps)
				return true;
			int r = -1;
			rep(i, 0, m) {
				if (D[i][s] <= eps)
					continue;
				if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i]) < MP(D[r][n + 1] / D[r][s], B[r]))
					r = i;
			}
			if (r == -1)
				return false;
			pivot(r, s);
		}
	}

	DOUBLE solve(vd &x) {
		int r = 0;
		rep(i, 1, m) if (D[i][n + 1] < D[r][n + 1]) r = i;
		if (D[r][n + 1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m + 1][n + 1] < -eps)
				return -inf;
			rep(i, 0, m) if (B[i] == -1) {
				int s = 0;
				rep(j, 1, n + 1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1);
		x = vd(n);
		rep(i, 0, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
		return ok ? D[m][n + 1] : inf;
	}
};
