// Crazy NTT mod 998244353 (=119*2^23+1) for N = 2^24
// https://judge.yosupo.jp/submission/103602
namespace crazy_ntt {
constexpr int N = 1 << 23;
constexpr int P = 998244353;

int w[N];

inline int add(int a, int b) { return a + b < P ? a + b : a + b - P; }

inline int sub(int a, int b) { return a - b < 0 ? a - b + P : a - b; }

inline int mul(int a, int b) { return int(1ll * a * b % P); }

inline int exp(int a, int x) {
	int b = 1;
	for (; x; x >>= 1) {
		if (x & 1)
			b = mul(a, b);
		a = mul(a, a);
	}
	return b;
}

void init(int n) {
	int g = exp(3, P / n);
	w[n / 2] = 1;
	for (int i = n / 2 + 1; i < n; ++i)
		w[i] = mul(w[i - 1], g);
	for (int i = n / 2 - 1; i > 0; --i)
		w[i] = w[i * 2];
}

void dft(int f[], int n) {
	for (int k = n / 2; k; k /= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; ++j) {
				int a = f[i + j];
				int b = f[i + j + k];
				f[i + j] = add(a, b);
				f[i + j + k] = mul(sub(a, b), w[k + j]);
			}
}

void ift(int f[], int n) {
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; ++j) {
				int a = f[i + j];
				int b = mul(f[i + j + k], w[k + j]);
				f[i + j] = add(a, b);
				f[i + j + k] = sub(a, b);
			}
	std::reverse(f + 1, f + n);
	int div = P - P / n;
	for (int i = 0; i < n; ++i)
		f[i] = mul(f[i], div);
}

int a[N << 2];
int b[N << 2];

vector<int> mult(vector<int> &_a, vector<int> &_b) {
	int n = sz(_a);
	int m = sz(_b);
	int o = 2;
	while(o < n + m - 1) o *= 2;
	for (int i = 0; i < n; ++i)
		a[i] = _a[i];
	for (int i = 0; i < m; ++i)
		b[i] = _b[i];
	if (o <= N) {
		init(o);
		dft(a, o);
		dft(b, o);
		for (int i = 0; i < o; ++i)
			a[i] = mul(a[i], b[i]);
		ift(a, o);
	} else {
		init(N);
		int h1 = 1;
		int h2 = 1;
		int h3 = 1;
		for (int i = 0; i < N; ++i) {
			int x = a[i + 0];
			int y = a[i + N];
			int z = b[i + 0];
			int w = b[i + N];
			a[i + N * 0] = add(x, y);
			// 470355006 ^ (2^24 - 1) = 1 mod 998244353.
			// 470355006 ^ 2 = 289156217 mod 998244353.
			// 470355006 ^ 3 = 785023286 mod 998244353.
			a[i + N * 1] = mul(add(x, mul(470355006, y)), h1);
			a[i + N * 2] = mul(add(x, mul(289156217, y)), h2);
			a[i + N * 3] = mul(add(x, mul(785023286, y)), h3);
			b[i + N * 0] = add(z, w);
			b[i + N * 1] = mul(add(z, mul(470355006, w)), h1);
			b[i + N * 2] = mul(add(z, mul(289156217, w)), h2);
			b[i + N * 3] = mul(add(z, mul(785023286, w)), h3);
			h1 = mul(h1, 3);
			h2 = mul(h2, 9);
			h3 = mul(h3, 27);
		}
		dft(a + N * 0, N);
		dft(a + N * 1, N);
		dft(a + N * 2, N);
		dft(a + N * 3, N);
		dft(b + N * 0, N);
		dft(b + N * 1, N);
		dft(b + N * 2, N);
		dft(b + N * 3, N);
		for (int i = 0; i < N * 4; ++i)
			a[i] = mul(a[i], b[i]);
		ift(a + N * 0, N);
		ift(a + N * 1, N);
		ift(a + N * 2, N);
		ift(a + N * 3, N);
		h1 = 1;
		h2 = 1;
		h3 = 1;
		for (int i = 0; i < N; ++i) {
			int x = a[i + N * 0];
			int y = mul(a[i + N * 1], h1);
			int z = mul(a[i + N * 2], h2);
			int w = mul(a[i + N * 3], h3);
			a[i + N * 0] = int((714390683ll * x + 11672785ll * y + 294849999ll * z + 975575240ll * w) % P);
			a[i + N * 1] = int((11672785ll * x + 963210248ll * y + 551341424ll * z + 470264249ll * w) % P);
			a[i + N * 2] = int((294849999ll * x + 551341424ll * y + 378958805ll * z + 771338478ll * w) % P);
			a[i + N * 3] = int((975575240ll * x + 470264249ll * y + 771338478ll * z + 777555092ll * w) % P);
			h1 = mul(h1, 332748118);
			h2 = mul(h2, 443664157);
			h3 = mul(h3, 480636170);
		}
	}
	vector<int> ans(a, a + n + m - 1);
	return ans;
}
} // namespace crazy_ntt
