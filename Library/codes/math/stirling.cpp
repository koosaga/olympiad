// Weird Lucas-like formula for Stirling Number
// Source: mostly https://judge.yosupo.jp/submission/100194
// Following fact could be useful:
// \sum_{i = [0, n]} S1(n, k) x^k = x(x-1) ... (x-n+1)
// S2(n, k) = \sum_{j = [1, k]} (-1)^{k-j} \frac{j^{n-1}}{(j-1)!(k-j)!}

namespace stirling {
int p;
vector<int> fact, invf;
vector<vector<int>> s1, s2;
void init(int MOD, int init_s1 = true, int init_s2 = true) {
	p = MOD;
	fact.resize(p);
	invf.resize(p);
	fact[0] = 1;
	for (int i = 1; i < p; i++) {
		fact[i] = 1ll * fact[i - 1] * i % p;
	}
	invf[p - 1] = p - 1;
	for (int i = p - 2; i >= 0; i--) {
		invf[i] = 1ll * invf[i + 1] * (i + 1) % p;
	}
	if (init_s1) {
		s1.resize(p);
		for (int i = 0; i < p; i++) {
			s1[i].resize(p);
			if (i == 0)
				s1[i][0] = 1;
			else {
				for (int j = 0; j <= i; j++) {
					if (j)
						s1[i][j] += s1[i - 1][j - 1];
					if (j < i)
						s1[i][j] += 1ll * s1[i - 1][j] * (p - i + 1) % p;
					if (s1[i][j] >= p)
						s1[i][j] -= p;
				}
			}
		}
	}
	if (init_s2) {
		s2.resize(p);
		for (int i = 0; i < p; i++) {
			s2[i].resize(p);
			if (i == 0)
				s2[i][0] = 1;
			else {
				for (int j = 0; j <= i; j++) {
					if (j)
						s2[i][j] += s2[i - 1][j - 1];
					if (j < i)
						s2[i][j] += 1ll * s2[i - 1][j] * j % p;
					if (s2[i][j] >= p)
						s2[i][j] -= p;
				}
			}
		}
	}
}
int binomFn(int x, int y) {
	if (y < 0 || x < y)
		return 0;
	return 1ll * fact[x] * (1ll * invf[y] * invf[x - y] % p) % p;
}
int binom(lint x, lint y) {
	lint ans = 1;
	while (x || y) {
		ans = ans * binomFn(x % p, y % p) % p;
		x /= p;
		y /= p;
	}
	return ans;
}
int S1(lint n, lint k) {
	if (k < 0 || k > n)
		return 0;
	lint i = n / p;
	int j = n % p;
	if (i > k)
		return 0;
	lint a = (k - i) / (p - 1);
	int b = (k - i) % (p - 1);
	if (b == 0 && j > 0) {
		b += (p - 1);
		a -= 1;
	}
	if (a < 0 || i < a || b > j)
		return 0;
	int x = binom(i, a);
	int y = s1[j][b];
	int res = 1ll * x * y % p;
	if ((i + a) % 2 == 1 && res) {
		res = p - res;
	}
	return res;
}

int S2(lint n, lint k) {
	if (k < 0 || k > n)
		return 0;
	if (n == 0)
		return 1;
	lint i = k / p;
	int j = k % p;
	if (n < i)
		return 0;
	lint a = (n - i) / (p - 1);
	int b = (n - i) - (p - 1) * a;
	if (b == 0) {
		b += p - 1;
		a -= 1;
	}
	if (a < 0 || j > b)
		return 0;
	if (b < p - 1) {
		return 1ll * binom(a, i) * s2[b][j] % p;
	}
	if (j == 0)
		return binom(a, i - 1);
	return 1ll * binom(a, i) * s2[p - 1][j] % p;
}
} // namespace stirling
