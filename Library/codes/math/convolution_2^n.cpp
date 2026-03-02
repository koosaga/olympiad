// Given two arrays a, b of length 2^n, compute c_k = sum((i*j) == k mod 2^n) a_i * b_j
// Credit: qwerasdfzxcl https://judge.yosupo.jp/submission/327703

using pol = poly<mint>;
vector<mint> gibum(const vector<mint> &f, const vector<mint> &g) {
	int n = f.size();
	int lg = countr_zero((unsigned)n);

	vector<vector<mint>> F[2], G[2], H[2];

	auto fuck = [&](vector<vector<mint>> F[], const vector<mint> &v, int p, int sz) {
		if (sz == 1) {
			F[0][p].resize(sz);
			F[0][p][0] = v[0];
		} else if (sz == 2) {
			F[0][p].resize(sz);
			F[0][p][0] = v[0], F[0][p][1] = v[1];
		} else {
			F[0][p].resize(sz / 2);
			F[1][p].resize(sz / 2);
			for (int z = 0; z < 2; z++) {
				lint cur = (!z) ? 1 : sz - 1;
				for (int i = 0; i < sz / 2; i++) {
					F[z][p][i] = v[cur / 2];
					cur = (cur * 5) & (sz * 2 - 1);
				}
			}
		}
	};

	auto ifuck = [&](vector<vector<mint>> F[], int p, int sz) -> vector<mint> {
		if (sz == 1)
			return {F[0][p][0]};
		else if (sz == 2)
			return {F[0][p][0], F[0][p][1]};
		vector<mint> ret(sz);
		for (int z = 0; z < 2; z++) {
			lint cur = (!z) ? 1 : sz - 1;
			for (int i = 0; i < sz / 2; i++) {
				ret[cur / 2] = F[z][p][i];
				cur = (cur * 5) & (sz * 2 - 1);
			}
		}
		return ret;
	};

	auto up = [&](vector<vector<mint>> F[], int p, int sz) {
		auto v = ifuck(F, p, sz << 1);
		for (int i = sz; i < (sz << 1); i++)
			v[i - sz] += v[i];
		v.resize(sz);
		fuck(F, v, p, sz);
	};

	auto push = [&](vector<vector<mint>> F[], const vector<mint> &f, int k, int sz) {
		if (sz <= 2)
			F[0].emplace_back(sz);
		else {
			F[0].emplace_back(sz >> 1);
			F[1].emplace_back(sz >> 1);
		}
		vector<mint> v(sz);
		for (int i = (1 << k), j = 0; i < n; i += (1 << (k + 1)), j++)
			v[j] = f[i];
		fuck(F, v, k, sz);
	};

	for (int k = 0; k < lg; k++) {
		int sz = n >> (k + 1);

		for (int p = 0; p < k; p++) {
			up(F, p, sz);
			up(G, p, sz);
		}

		push(F, f, k, sz);
		push(G, g, k, sz);

		int lim = (sz <= 2) ? 1 : 2;
		int sz2 = sz / lim;
		H[0].emplace_back(sz2);
		if (sz > 2)
			H[1].emplace_back(sz2);

		for (int p = 0; p <= k; p++) {
			for (int zf = 0; zf < lim; zf++) {
				for (int zg = 0; zg < lim; zg++) {
					int zh = (zf + zg) % 2;
					auto res = pol(F[zf][p]) * pol(G[zg][k - p]);
					for (int i = 0; i < sz2; i++)
						H[zh][k][i] += res[i];
					for (int i = sz2; i <= res.deg(); i++)
						H[zh][k][i - sz2] += res[i];
				}
			}
		}
	}

	vector<mint> ret(n);

	for (int i = 0; i < n; i++)
		ret[0] += f[0] * g[i] + f[i] * g[0];
	ret[0] -= f[0] * g[0];

	for (int p = 0; p < lg; p++)
		for (int q = 0; q < lg; q++)
			if (p + q >= lg)
				ret[0] += F[0][p][0] * G[0][q][0];

	for (int k = 0; k < lg; k++) {
		int sz = n >> (k + 1);
		auto v = ifuck(H, k, sz);
		for (int i = (1 << k), j = 0; i < n; i += (1 << (k + 1)), j++)
			ret[i] = v[j];
	}

	return ret;
}