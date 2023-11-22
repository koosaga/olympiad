#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 998244353; // 1e9 + 7;//993244853;

// Multivariate convolution (truncated)
// Each index i = i[0] + i[1] * n[0] + i[2] * n[0] * n[1] + ...
// Source: https://judge.yosupo.jp/submission/74099

int countr_zero(unsigned int n) { return __builtin_ctz(n); }
constexpr int countr_zero_constexpr(unsigned int n) {
	int x = 0;
	while (!(n & (1 << x)))
		x++;
	return x;
}
struct fft_info {
	static constexpr int g = 3; // primitive root
	static constexpr int rank2 = countr_zero_constexpr(mod - 1);
	array<mint, rank2 + 1> root;  // root[i]^(2^i) == 1
	array<mint, rank2 + 1> iroot; // root[i] * iroot[i] == 1

	array<mint, max(0, rank2 - 2 + 1)> rate2;
	array<mint, max(0, rank2 - 2 + 1)> irate2;

	array<mint, max(0, rank2 - 3 + 1)> rate3;
	array<mint, max(0, rank2 - 3 + 1)> irate3;

	fft_info() {
		root[rank2] = ipow(mint(g), ((mod - 1) >> rank2));
		iroot[rank2] = root[rank2].inv();
		for (int i = rank2 - 1; i >= 0; i--) {
			root[i] = root[i + 1] * root[i + 1];
			iroot[i] = iroot[i + 1] * iroot[i + 1];
		}

		{
			mint prod = 1, iprod = 1;
			for (int i = 0; i <= rank2 - 2; i++) {
				rate2[i] = root[i + 2] * prod;
				irate2[i] = iroot[i + 2] * iprod;
				prod *= iroot[i + 2];
				iprod *= root[i + 2];
			}
		}
		{
			mint prod = 1, iprod = 1;
			for (int i = 0; i <= rank2 - 3; i++) {
				rate3[i] = root[i + 3] * prod;
				irate3[i] = iroot[i + 3] * iprod;
				prod *= iroot[i + 3];
				iprod *= root[i + 3];
			}
		}
	}
};

void butterfly(vector<mint> &a) {
	int n = int(a.size());
	int h = countr_zero((unsigned int)n);

	static const fft_info info;

	int len = 0; // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
	while (len < h) {
		if (h - len == 1) {
			int p = 1 << (h - len - 1);
			mint rot = 1;
			for (int s = 0; s < (1 << len); s++) {
				int offset = s << (h - len);
				for (int i = 0; i < p; i++) {
					auto l = a[i + offset];
					auto r = a[i + offset + p] * rot;
					a[i + offset] = l + r;
					a[i + offset + p] = l - r;
				}
				if (s + 1 != (1 << len))
					rot *= info.rate2[countr_zero(~(unsigned int)(s))];
			}
			len++;
		} else {
			// 4-base
			int p = 1 << (h - len - 2);
			mint rot = 1, imag = info.root[2];
			for (int s = 0; s < (1 << len); s++) {
				mint rot2 = rot * rot;
				mint rot3 = rot2 * rot;
				int offset = s << (h - len);
				for (int i = 0; i < p; i++) {
					auto mod2 = 1ULL * mod * mod;
					auto a0 = 1ULL * a[i + offset].val;
					auto a1 = 1ULL * a[i + offset + p].val * rot.val;
					auto a2 = 1ULL * a[i + offset + 2 * p].val * rot2.val;
					auto a3 = 1ULL * a[i + offset + 3 * p].val * rot3.val;
					auto a1na3imag = 1ULL * mint(a1 + mod2 - a3).val * imag.val;
					auto na2 = mod2 - a2;
					a[i + offset] = a0 + a2 + a1 + a3;
					a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
					a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
					a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
				}
				if (s + 1 != (1 << len))
					rot *= info.rate3[countr_zero(~(unsigned int)(s))];
			}
			len += 2;
		}
	}
}
void butterfly_inv(vector<mint> &a) {
	int n = int(a.size());
	int h = countr_zero((unsigned int)n);

	static const fft_info info;

	int len = h; // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
	while (len) {
		if (len == 1) {
			int p = 1 << (h - len);
			mint irot = 1;
			for (int s = 0; s < (1 << (len - 1)); s++) {
				int offset = s << (h - len + 1);
				for (int i = 0; i < p; i++) {
					auto l = a[i + offset];
					auto r = a[i + offset + p];
					a[i + offset] = l + r;
					a[i + offset + p] = (unsigned long long)(mod + l.val - r.val) * irot.val;
					;
				}
				if (s + 1 != (1 << (len - 1)))
					irot *= info.irate2[countr_zero(~(unsigned int)(s))];
			}
			len--;
		} else {
			// 4-base
			int p = 1 << (h - len);
			mint irot = 1, iimag = info.iroot[2];
			for (int s = 0; s < (1 << (len - 2)); s++) {
				mint irot2 = irot * irot;
				mint irot3 = irot2 * irot;
				int offset = s << (h - len + 2);
				for (int i = 0; i < p; i++) {
					auto a0 = 1ULL * a[i + offset + 0 * p].val;
					auto a1 = 1ULL * a[i + offset + 1 * p].val;
					auto a2 = 1ULL * a[i + offset + 2 * p].val;
					auto a3 = 1ULL * a[i + offset + 3 * p].val;

					auto a2na3iimag = 1ULL * mint((mod + a2 - a3) * iimag.val).val;

					a[i + offset] = a0 + a1 + a2 + a3;
					a[i + offset + 1 * p] = (a0 + (mod - a1) + a2na3iimag) * irot.val;
					a[i + offset + 2 * p] = (a0 + a1 + (mod - a2) + (mod - a3)) * irot2.val;
					a[i + offset + 3 * p] = (a0 + (mod - a1) + (mod - a2na3iimag)) * irot3.val;
				}
				if (s + 1 != (1 << (len - 2)))
					irot *= info.irate3[countr_zero(~(unsigned int)(s))];
			}
			len -= 2;
		}
	}
}

struct multi_variate_convolution {
	multi_variate_convolution() : multi_variate_convolution(vector<int>{}) {}
	multi_variate_convolution(const vector<int> &dim) : _n(accumulate(dim.begin(), dim.end(), 1, multiplies<int>())), _k(dim.size()), _m(ceil_pow2(_n)), _chi(_n, 0) {
		for (int i = 0; i < _n; ++i) {
			int den = 1;
			for (int e : dim)
				den *= e, _chi[i] += i / den;
			if (_k)
				_chi[i] %= _k;
		}
	}

	int size() const { return _n; }
	int dim_num() const { return _k; }
	using T = mint;
	vector<T> convolution(vector<T> f, vector<T> g) const {
		assert(int(f.size()) == _n and int(g.size()) == _n);
		if (_k == 0)
			return {f[0] * g[0]};
		auto rf = ranked(f), rg = ranked(g);

		for (auto &v : rf)
			butterfly(v);
		for (auto &v : rg)
			butterfly(v);
		vector rh(_k, vector<T>(_m, T{}));
		for (int i = 0; i < _k; ++i)
			for (int j = 0; j < _k; ++j) {
				int r = i + j < _k ? i + j : i + j - _k;
				for (int p = 0; p < _m; ++p)
					rh[r][p] += rf[i][p] * rg[j][p];
			}
		for (auto &v : rh)
			butterfly_inv(v);
		const T isz = mint(1) / mint(T(_m));
		vector<T> h(_n);
		for (int i = 0; i < _n; ++i)
			h[i] = rh[_chi[i]][i] * isz;
		return h;
	}

  private:
	int _n, _k, _m;
	vector<int> _chi;

	static constexpr int ceil_pow2(int m) {
		int res = 1;
		while (res < m)
			res *= 2;
		return res * 2;
	}

	vector<vector<T>> ranked(const vector<T> &f) const {
		vector rf(_k, vector<T>(_m, T{}));
		for (int i = 0; i < _n; ++i)
			rf[_chi[i]][i] = f[i];
		return rf;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k;
	cin >> k;
	vector<int> n(k);
	int p = 1;
	for (auto &x : n)
		cin >> x, p *= x;
	vector<mint> a(p), b(p);
	for (auto &x : a)
		cin >> x.val;
	for (auto &x : b)
		cin >> x.val;
	auto mvc = multi_variate_convolution(n);

	auto c = mvc.convolution(a, b);
	for (auto &z : c) {
		cout << z << " ";
	}
}
