// Multivariate convolution (truncated)
// Each index i = i[0] + i[1] * n[0] + i[2] * n[0] * n[1] + ...
// Source: qwerasdfzxcl https://judge.yosupo.jp/submission/355934

template <class T> vector<T> gibum(const std::vector<T> &f, const std::vector<T> &g, const std::vector<int> &d) {
	int n = f.size(), k = d.size();
	if (n == 1) {
		return vector<T>{f[0] * g[0]};
	}
	std::vector<int> I(f.size());

	for (int i = 0, p = d[0]; i < k - 1; p *= d[++i]) {
		for (int j = 0, v = 0; j < n; j += p, v++) {
			if (v == k)
				v = 0;
			for (int t = j; t < j + p; t++) {
				I[t] += v;
				if (I[t] >= k)
					I[t] -= k;
			}
		}
	}

	int sz = 1;
	while (sz < n)
		sz *= 2;
	sz *= 2;

	std::vector<std::vector<T>> F(k, std::vector<T>(sz)), G(k, std::vector<T>(sz));

	for (int i = 0; i < n; i++)
		F[I[i]][i] = f[i], G[I[i]][i] = g[i];
	for (int i = 0; i < k; i++)
		fft::ntt(F[i], 0), fft::ntt(G[i], 0);

	std::vector<std::vector<T>> H(k, std::vector<T>(sz));
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++) {
			for (int t = 0; t < sz; t++)
				H[(i + j) % k][t] += F[i][t] * G[j][t];
		}

	for (int i = 0; i < k; i++)
		fft::ntt(H[i], 1);

	T ninv = T(sz).inv();
	std::vector<T> ret(n);
	for (int i = 0; i < n; i++)
		ret[i] = H[I[i]][i];
	return ret;
}
