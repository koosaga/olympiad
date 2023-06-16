#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 998244353; // 1e9 + 7;//993244853;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// To use polynomial sqrt, need to amend sqrt for modint.

struct mint {
	int val;
	mint() { val = 0; }
	mint(const lint &v) {
		val = (-mod <= v && v < mod) ? v : v % mod;
		if (val < 0)
			val += mod;
	}

	friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
	friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
	friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
	friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

	mint operator-() const { return mint(-val); }
	mint &operator+=(const mint &m) {
		if ((val += m.val) >= mod)
			val -= mod;
		return *this;
	}
	mint &operator-=(const mint &m) {
		if ((val -= m.val) < 0)
			val += mod;
		return *this;
	}
	mint &operator*=(const mint &m) {
		val = (lint)val * m.val % mod;
		return *this;
	}
	friend mint ipow(mint a, lint p) {
		mint ans = 1;
		for (; p; p /= 2, a *= a)
			if (p & 1)
				ans *= a;
		return ans;
	}
	mint inv() const { return ipow(*this, mod - 2); }
	mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

namespace fft {
using real_t = double;
using base = complex<real_t>;

void fft(vector<base> &a, bool inv) {
	int n = a.size(), j = 0;
	vector<base> roots(n / 2);
	for (int i = 1; i < n; i++) {
		int bit = (n >> 1);
		while (j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}
	real_t ang = 2 * acos(real_t(-1)) / n * (inv ? -1 : 1);
	for (int i = 0; i < n / 2; i++) {
		roots[i] = base(cos(ang * i), sin(ang * i));
	}
	/*
	   XOR Convolution : set roots[*] = 1.
	   OR Convolution  : It's easy, don't try to use FFT. https://codeforces.com/blog/entry/115438
	 */
	for (int i = 2; i <= n; i <<= 1) {
		int step = n / i;
		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < i / 2; k++) {
				base u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}
	if (inv)
		for (int i = 0; i < n; i++)
			a[i] /= n; 
}
template <typename T> void ntt(vector<T> &a, bool inv) {
	const int prr = 3; // primitive root
	int n = a.size(), j = 0;
	vector<T> roots(n / 2);
	for (int i = 1; i < n; i++) {
		int bit = (n >> 1);
		while (j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}
	T ang = ipow(T(prr), (mod - 1) / n);
	if (inv)
		ang = T(1) / ang;
	for (int i = 0; i < n / 2; i++) {
		roots[i] = (i ? (roots[i - 1] * ang) : T(1));
	}
	for (int i = 2; i <= n; i <<= 1) {
		int step = n / i;
		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < i / 2; k++) {
				T u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}
	if (inv) {
		T rev = T(1) / T(n);
		for (int i = 0; i < n; i++)
			a[i] *= rev;
	}
}
template <typename T> vector<T> multiply_ntt(vector<T> &v, const vector<T> &w) {
	vector<T> fv(all(v)), fw(all(w));
	int n = 2;
	while (n < sz(v) + sz(w))
		n <<= 1;
	fv.resize(n);
	fw.resize(n);
	ntt(fv, 0);
	ntt(fw, 0);
	for (int i = 0; i < n; i++)
		fv[i] *= fw[i];
	ntt(fv, 1);
	vector<T> ret(n);
	for (int i = 0; i < n; i++)
		ret[i] = fv[i];
	return ret;
}
template <typename T> vector<T> multiply(vector<T> &v, const vector<T> &w) {
	vector<base> fv(all(v)), fw(all(w));
	int n = 2;
	while (n < sz(v) + sz(w))
		n <<= 1;
	fv.resize(n);
	fw.resize(n);
	fft(fv, 0);
	fft(fw, 0);
	for (int i = 0; i < n; i++)
		fv[i] *= fw[i];
	fft(fv, 1);
	vector<T> ret(n);
	for (int i = 0; i < n; i++)
		ret[i] = (T)llround(fv[i].real());
	return ret;
}
template <typename T> vector<T> multiply_mod(vector<T> v, const vector<T> &w) {
	int n = 2;
	while (n < sz(v) + sz(w))
		n <<= 1;
	vector<base> v1(n), v2(n), r1(n), r2(n);
	for (int i = 0; i < v.size(); i++) {
		v1[i] = base(v[i] >> 15, v[i] & 32767);
	}
	for (int i = 0; i < w.size(); i++) {
		v2[i] = base(w[i] >> 15, w[i] & 32767);
	}
	fft(v1, 0);
	fft(v2, 0);
	for (int i = 0; i < n; i++) {
		int j = (i ? (n - i) : i);
		base ans1 = (v1[i] + conj(v1[j])) * base(0.5, 0);
		base ans2 = (v1[i] - conj(v1[j])) * base(0, -0.5);
		base ans3 = (v2[i] + conj(v2[j])) * base(0.5, 0);
		base ans4 = (v2[i] - conj(v2[j])) * base(0, -0.5);
		r1[i] = (ans1 * ans3) + (ans1 * ans4) * base(0, 1);
		r2[i] = (ans2 * ans3) + (ans2 * ans4) * base(0, 1);
	}
	fft(r1, 1);
	fft(r2, 1);
	vector<T> ret(n);
	for (int i = 0; i < n; i++) {
		T av = llround(r1[i].real());
		T bv = llround(r1[i].imag()) + llround(r2[i].real());
		T cv = llround(r2[i].imag());
		av = av << 30;
		bv = bv << 15;
		ret[i] = av + bv + cv;
	}
	return ret;
}
template <typename T> vector<T> multiply_naive(vector<T> v, const vector<T> &w) {
	if (sz(v) == 0 || sz(w) == 0)
		return vector<T>();
	vector<T> ret(sz(v) + sz(w) - 1);
	for (int i = 0; i < sz(v); i++) {
		for (int j = 0; j < sz(w); j++) {
			ret[i + j] += v[i] * w[j];
		}
	}
	return ret;
}

} // namespace fft

const int maxn = 1 << 20;
const int magic = 250; // threshold for sizes to run the naive algo

template <typename T> T fact(int n) {
	static T F[maxn];
	static bool init = false;
	if (!init) {
		F[0] = T(1);
		for (int i = 1; i < maxn; i++) {
			F[i] = F[i - 1] * T(i);
		}
		init = true;
	}
	return F[n];
}

template <typename T> T rfact(int n) {
	static T F[maxn];
	static bool init = false;
	if (!init) {
		F[maxn - 1] = T(1) / fact<T>(maxn - 1);
		for (int i = maxn - 2; i >= 0; i--) {
			F[i] = F[i + 1] * T(i + 1);
		}
		init = true;
	}
	return F[n];
}

template <typename T> struct poly {
	vector<T> a;

	void normalize() { // get rid of leading zeroes
		while (!a.empty() && a.back() == T(0)) {
			a.pop_back();
		}
	}

	poly() {}
	poly(T a0) : a{a0} { normalize(); }
	poly(const vector<T> &t) : a(t) { normalize(); }

	poly operator-() const {
		auto t = *this;
		for (auto &it : t.a) {
			it = -it;
		}
		return t;
	}

	poly operator+=(const poly &t) {
		a.resize(max(a.size(), t.a.size()));
		for (size_t i = 0; i < t.a.size(); i++) {
			a[i] += t.a[i];
		}
		normalize();
		return *this;
	}

	poly operator-=(const poly &t) {
		a.resize(max(a.size(), t.a.size()));
		for (size_t i = 0; i < t.a.size(); i++) {
			a[i] -= t.a[i];
		}
		normalize();
		return *this;
	}
	poly operator+(const poly &t) const { return poly(*this) += t; }
	poly operator-(const poly &t) const { return poly(*this) -= t; }

	poly mod_xk(size_t k) const { // get first k coefficients
		return vector<T>(begin(a), begin(a) + min(k, a.size()));
	}

	poly mul_xk(size_t k) const { // multiply by x^k
		auto res = a;
		res.insert(begin(res), k, 0);
		return res;
	}

	poly div_xk(size_t k) const { // drop first k coefficients
		return vector<T>(begin(a) + min(k, a.size()), end(a));
	}

	poly substr(size_t l, size_t r) const { // return mod_xk(r).div_xk(l)
		return vector<T>(begin(a) + min(l, a.size()), begin(a) + min(r, a.size()));
	}

	poly operator*=(const poly &t) {
		a = fft::multiply_ntt(a, t.a);
		normalize();
		return *this;
	}
	poly operator*(const poly &t) const { return poly(*this) *= t; }

	poly reverse(size_t n) const { // computes x^n A(x^{-1})
		auto res = a;
		res.resize(max(n, res.size()));
		return vector<T>(res.rbegin(), res.rbegin() + n);
	}

	poly reverse() const { return reverse(deg() + 1); }

	pair<poly, poly> divmod_slow(const poly &b) const { // when divisor or quotient is small
		vector<T> A(a);
		vector<T> res;
		while (A.size() >= b.a.size()) {
			res.push_back(A.back() / b.a.back());
			if (res.back() != T(0)) {
				for (size_t i = 0; i < b.a.size(); i++) {
					A[A.size() - i - 1] -= res.back() * b.a[b.a.size() - i - 1];
				}
			}
			A.pop_back();
		}
		std::reverse(begin(res), end(res));
		return {res, A};
	}

	pair<poly, poly> divmod_hint(poly const &b, poly const &binv) const { // when inverse is known
		assert(!b.is_zero());
		if (deg() < b.deg()) {
			return {poly{0}, *this};
		}
		int d = deg() - b.deg();
		if (min(d, b.deg()) < magic) {
			return divmod_slow(b);
		}
		poly D = (reverse().mod_xk(d + 1) * binv.mod_xk(d + 1)).mod_xk(d + 1).reverse(d + 1);
		return {D, *this - D * b};
	}

	pair<poly, poly> divmod(const poly &b) const { // returns quotiend and remainder of a mod b
		assert(!b.is_zero());
		if (deg() < b.deg()) {
			return {poly{0}, *this};
		}
		int d = deg() - b.deg();
		if (min(d, b.deg()) < magic) {
			return divmod_slow(b);
		}
		poly D = (reverse().mod_xk(d + 1) * b.reverse().inv(d + 1)).mod_xk(d + 1).reverse(d + 1);
		return {D, *this - D * b};
	}

	// (ax+b) / (cx+d)
	struct transform {
		poly a, b, c, d;
		transform(poly a, poly b = T(1), poly c = T(1), poly d = T(0)) : a(a), b(b), c(c), d(d) {}

		transform operator*(transform const &t) { return {a * t.a + b * t.c, a * t.b + b * t.d, c * t.a + d * t.c, c * t.b + d * t.d}; }

		transform adj() { return transform(d, -b, -c, a); }

		auto apply(poly A, poly B) { return make_pair(a * A + b * B, c * A + d * B); }
	};

	template <typename Q> static void concat(vector<Q> &a, vector<Q> const &b) {
		for (auto it : b) {
			a.push_back(it);
		}
	}

	// finds a transform that changes A/B to A'/B' such that
	// deg B' is at least 2 times less than deg A
	static pair<vector<poly>, transform> half_gcd(poly A, poly B) {
		assert(A.deg() >= B.deg());
		int m = (A.deg() + 1) / 2;
		if (B.deg() < m) {
			return {{}, {T(1), T(0), T(0), T(1)}};
		}
		auto [ar, Tr] = half_gcd(A.div_xk(m), B.div_xk(m));
		tie(A, B) = Tr.adj().apply(A, B);
		if (B.deg() < m) {
			return {ar, Tr};
		}
		auto [ai, R] = A.divmod(B);
		tie(A, B) = make_pair(B, R);
		int k = 2 * m - B.deg();
		auto [as, Ts] = half_gcd(A.div_xk(k), B.div_xk(k));
		concat(ar, {ai});
		concat(ar, as);
		return {ar, Tr * transform(ai) * Ts};
	}

	// return a transform that reduces A / B to gcd(A, B) / 0
	static pair<vector<poly>, transform> full_gcd(poly A, poly B) {
		vector<poly> ak;
		vector<transform> trs;
		while (!B.is_zero()) {
			if (2 * B.deg() > A.deg()) {
				auto [a, Tr] = half_gcd(A, B);
				concat(ak, a);
				trs.push_back(Tr);
				tie(A, B) = trs.back().adj().apply(A, B);
			} else {
				auto [a, R] = A.divmod(B);
				ak.push_back(a);
				trs.emplace_back(a);
				tie(A, B) = make_pair(B, R);
			}
		}
		trs.emplace_back(T(1), T(0), T(0), T(1));
		while (trs.size() >= 2) {
			trs[trs.size() - 2] = trs[trs.size() - 2] * trs[trs.size() - 1];
			trs.pop_back();
		}
		return {ak, trs.back()};
	}

	static poly gcd(poly A, poly B) {
		if (A.deg() < B.deg()) {
			return full_gcd(B, A);
		}
		auto Tr = fraction(A, B);
		return Tr.d * A - Tr.b * B;
	}

	// Returns the characteristic polynomial
	// of the minimum linear recurrence for the sequence
	poly min_rec_slow(int d) const {
		auto R1 = mod_xk(d + 1).reverse(d + 1), R2 = xk(d + 1);
		auto Q1 = poly(T(1)), Q2 = poly(T(0));
		while (!R2.is_zero()) {
			auto [a, nR] = R1.divmod(R2); // R1 = a*R2 + nR, deg nR < deg R2
			tie(R1, R2) = make_tuple(R2, nR);
			tie(Q1, Q2) = make_tuple(Q2, Q1 + a * Q2);
			if (R2.deg() < Q2.deg()) {
				return Q2 / Q2.lead();
			}
		}
		assert(0);
	}

	// calculate inv to *this modulo t
	// quadratic complexity
	optional<poly> inv_mod_slow(poly const &t) const {
		auto R1 = *this, R2 = t;
		auto Q1 = poly(T(1)), Q2 = poly(T(0));
		int k = 0;
		while (!R2.is_zero()) {
			k ^= 1;
			auto [a, nR] = R1.divmod(R2);
			tie(R1, R2) = make_tuple(R2, nR);
			tie(Q1, Q2) = make_tuple(Q2, Q1 + a * Q2);
		}
		if (R1.deg() > 0) {
			return nullopt;
		} else {
			return (k ? -Q1 : Q1) / R1[0];
		}
	}

	optional<poly> inv_mod(poly const &t) const {
		assert(!t.is_zero());
		if (false && min(deg(), t.deg()) < magic) {
			return inv_mod_slow(t);
		}
		auto A = t, B = *this % t;
		auto [a, Tr] = full_gcd(A, B);
		auto g = Tr.d * A - Tr.b * B;
		if (g.deg() != 0) {
			return nullopt;
		}
		return -Tr.b / g[0];
	};

	poly operator/(const poly &t) const { return divmod(t).first; }
	poly operator%(const poly &t) const { return divmod(t).second; }
	poly operator/=(const poly &t) { return *this = divmod(t).first; }
	poly operator%=(const poly &t) { return *this = divmod(t).second; }
	poly operator*=(const T &x) {
		for (auto &it : a) {
			it *= x;
		}
		normalize();
		return *this;
	}
	poly operator/=(const T &x) {
		for (auto &it : a) {
			it /= x;
		}
		normalize();
		return *this;
	}
	poly operator*(const T &x) const { return poly(*this) *= x; }
	poly operator/(const T &x) const { return poly(*this) /= x; }

	poly conj() const { // A(x) -> A(-x)
		auto res = *this;
		for (int i = 1; i <= deg(); i += 2) {
			res[i] = -res[i];
		}
		return res;
	}

	void print(int n) const {
		for (int i = 0; i < n; i++) {
			cout << (*this)[i] << ' ';
		}
		cout << "\n";
	}

	void print() const { print(deg() + 1); }

	T eval(T x) const { // evaluates in single point x
		T res(0);
		for (int i = deg(); i >= 0; i--) {
			res *= x;
			res += a[i];
		}
		return res;
	}

	T lead() const { // leading coefficient
		assert(!is_zero());
		return a.back();
	}

	int deg() const { // degree, -1 for P(x) = 0
		return (int)a.size() - 1;
	}

	bool is_zero() const { return a.empty(); }

	T operator[](int idx) const { return idx < 0 || idx > deg() ? T(0) : a[idx]; }

	T &coef(size_t idx) { // mutable reference at coefficient
		return a[idx];
	}

	bool operator==(const poly &t) const { return a == t.a; }
	bool operator!=(const poly &t) const { return a != t.a; }

	poly deriv(int k = 1) { // calculate derivative
		if (deg() + 1 < k) {
			return poly(T(0));
		}
		vector<T> res(deg() + 1 - k);
		for (int i = k; i <= deg(); i++) {
			res[i - k] = fact<T>(i) * rfact<T>(i - k) * a[i];
		}
		return res;
	}

	poly integr() { // calculate integral with C = 0
		vector<T> res(deg() + 2);
		for (int i = 0; i <= deg(); i++) {
			res[i + 1] = a[i] / T(i + 1);
		}
		return res;
	}

	size_t trailing_xk() const { // Let p(x) = x^k * t(x), return k
		if (is_zero()) {
			return -1;
		}
		int res = 0;
		while (a[res] == T(0)) {
			res++;
		}
		return res;
	}

	poly log(size_t n) { // calculate log p(x) mod x^n
		assert(a[0] == T(1));
		return (deriv().mod_xk(n) * inv(n)).integr().mod_xk(n);
	}

	poly exp(size_t n) { // calculate exp p(x) mod x^n
		if (is_zero()) {
			return T(1);
		}
		assert(a[0] == T(0));
		poly ans = T(1);
		size_t a = 1;
		while (a < n) {
			poly C = ans.log(2 * a).div_xk(a) - substr(a, 2 * a);
			ans -= (ans * C).mod_xk(a).mul_xk(a);
			a *= 2;
		}
		return ans.mod_xk(n);
	}

	poly pow_bin(int64_t k, size_t n) { // O(n log n log k)
		if (k == 0) {
			return poly(1).mod_xk(n);
		} else {
			auto t = pow(k / 2, n);
			t *= t;
			return (k % 2 ? *this * t : t).mod_xk(n);
		}
	}

	// Do not compute inverse from scratch
	poly powmod_hint(int64_t k, poly const &md, poly const &mdinv) {
		if (k == 0) {
			return poly(1);
		} else {
			auto t = powmod_hint(k / 2, md, mdinv);
			t = (t * t).divmod_hint(md, mdinv).second;
			if (k % 2) {
				t = (t * *this).divmod_hint(md, mdinv).second;
			}
			return t;
		}
	}

	poly powmod(int64_t k, poly const &md) {
		auto mdinv = md.reverse().inv(md.deg() + 1);
		return powmod_hint(k, md, mdinv);
	}

	// O(d * n) with the derivative trick from
	// https://codeforces.com/blog/entry/73947?#comment-581173
	poly pow_dn(int64_t k, size_t n) {
		if (n == 0) {
			return poly(T(0));
		}
		assert((*this)[0] != T(0));
		vector<T> Q(n);
		Q[0] = ipow(a[0], k);
		for (int i = 1; i < (int)n; i++) {
			for (int j = 1; j <= min(deg(), i); j++) {
				Q[i] += a[j] * Q[i - j] * (T(k) * T(j) - T(i - j));
			}
			Q[i] /= T(i) * a[0];
		}
		return Q;
	}

	// calculate p^k(n) mod x^n in O(n log n)
	// might be quite slow due to high constant
	poly pow(int64_t k, size_t n) {
		if (is_zero()) {
			return k ? *this : poly(1);
		}
		int i = trailing_xk();
		if (i > 0) {
			return k >= int64_t(n + i - 1) / i ? poly(T(0)) : div_xk(i).pow(k, n - i * k).mul_xk(i * k);
		}
		if (min(deg(), (int)n) <= magic) {
			return pow_dn(k, n);
		}
		if (k <= magic) {
			return pow_bin(k, n);
		}
		T j = a[i];
		poly t = *this / j;
		return ((t.log(n) * T(k)).exp(n).mod_xk(n)) * ipow(j, k);
	}

	// returns nullopt if undefined
	optional<poly> sqrt(size_t n) const {
		if (is_zero()) {
			return *this;
		}
		int i = trailing_xk();
		if (i % 2) {
			return nullopt;
		} else if (i > 0) {
			auto ans = div_xk(i).sqrt(n - i / 2);
			return ans ? ans->mul_xk(i / 2) : ans;
		}
		// do it or assume this to be 1
		auto st = (*this)[0].sqrt();
		if (st) {
			poly ans = *st;
			size_t a = 1;
			while (a < n) {
				a *= 2;
				ans -= (ans - mod_xk(a) * ans.inv(a)).mod_xk(a) / 2;
			}
			return ans.mod_xk(n);
		}
		return nullopt;
	}

	poly mulx(T a) const { // component-wise multiplication with a^k
		T cur = 1;
		poly res(*this);
		for (int i = 0; i <= deg(); i++) {
			res.coef(i) *= cur;
			cur *= a;
		}
		return res;
	}

	poly mulx_sq(T a) const { // component-wise multiplication with a^{k^2}
		T cur = a;
		T total = 1;
		T aa = a * a;
		poly res(*this);
		for (int i = 0; i <= deg(); i++) {
			res.coef(i) *= total;
			total *= cur;
			cur *= aa;
		}
		return res;
	}

	vector<T> chirpz_even(T z, int n) const { // P(1), P(z^2), P(z^4), ..., P(z^2(n-1))
		int m = deg();
		if (is_zero()) {
			return vector<T>(n, 0);
		}
		vector<T> vv(m + n);
		T zi = T(1) / z;
		T zz = zi * zi;
		T cur = zi;
		T total = 1;
		for (int i = 0; i <= max(n - 1, m); i++) {
			if (i <= m) {
				vv[m - i] = total;
			}
			if (i < n) {
				vv[m + i] = total;
			}
			total *= cur;
			cur *= zz;
		}
		poly w = (mulx_sq(z) * vv).substr(m, m + n).mulx_sq(z);
		vector<T> res(n);
		for (int i = 0; i < n; i++) {
			res[i] = w[i];
		}
		return res;
	}

	vector<T> chirpz(T z, int n) const { // P(1), P(z), P(z^2), ..., P(z^(n-1))
		if (is_zero() || n == 0) {
			return vector<T>(n);
		}
		if (z == T(0) || n == 1) {
			vector<T> ans(n, a[0]);
			for (int i = 1; i <= deg(); i++)
				ans[0] += a[i];
			return ans;
		}
		auto even = chirpz_even(z, (n + 1) / 2);
		auto odd = mulx(z).chirpz_even(z, n / 2);
		vector<T> ans(n);
		for (int i = 0; i < n / 2; i++) {
			ans[2 * i] = even[i];
			ans[2 * i + 1] = odd[i];
		}
		if (n % 2 == 1) {
			ans[n - 1] = even.back();
		}
		return ans;
	}

	static auto resultant(poly a, poly b) { // computes resultant of a and b
		if (b.is_zero()) {
			return 0;
		} else if (b.deg() == 0) {
			return bpow(b.lead(), a.deg());
		} else {
			int pw = a.deg();
			a %= b;
			pw -= a.deg();
			auto mul = bpow(b.lead(), pw) * T((b.deg() & a.deg() & 1) ? -1 : 1);
			auto ans = resultant(b, a);
			return ans * mul;
		}
	}

	static poly xk(size_t n) { // P(x) = x^n
		return poly(T(1)).mul_xk(n);
	}

	static poly ones(size_t n) { // P(x) = 1 + x + ... + x^{n-1}
		return vector<T>(n, 1);
	}

	static poly expx(size_t n) { // P(x) = e^x (mod x^n)
		return ones(n).borel();
	}

	// [x^k] (a corr b) = sum_{i+j=k} ai*b{m-j}
	//                  = sum_{i-j=k-m} ai*bj
	static poly corr(poly a, poly b) { // cross-correlation
		return a * b.reverse();
	}

	poly invborel() const { // ak *= k!
		auto res = *this;
		for (int i = 0; i <= deg(); i++) {
			res.coef(i) *= fact<T>(i);
		}
		return res;
	}

	poly borel() const { // ak /= k!
		auto res = *this;
		for (int i = 0; i <= deg(); i++) {
			res.coef(i) *= rfact<T>(i);
		}
		return res;
	}

	poly shift(T a) const { // P(x + a)
		return (expx(deg() + 1).mulx(a).reverse() * invborel()).div_xk(deg()).borel();
	}

	poly x2() { // P(x) -> P(x^2)
		vector<T> res(2 * a.size());
		for (size_t i = 0; i < a.size(); i++) {
			res[2 * i] = a[i];
		}
		return res;
	}

	// Return {P0, P1}, where P(x) = P0(x) + xP1(x)
	pair<poly, poly> bisect() const {
		vector<T> res[2];
		res[0].reserve(deg() / 2 + 1);
		res[1].reserve(deg() / 2 + 1);
		for (int i = 0; i <= deg(); i++) {
			res[i % 2].push_back(a[i]);
		}
		return {res[0], res[1]};
	}

	poly inv(int n) {
		poly q(a[0].inv());
		for (int i = 1; i < n; i <<= 1) {
			poly p = poly(2) - q * mod_xk(i * 2);
			q = (p * q).mod_xk(i * 2);
		}
		return q.mod_xk(n);
	}
	// compute A(B(x)) mod x^n in O(n^2)
	static poly compose(poly A, poly B, int n) {
		int q = std::sqrt(n);
		vector<poly> Bk(q);
		auto Bq = B.pow(q, n);
		Bk[0] = poly(T(1));
		for (int i = 1; i < q; i++) {
			Bk[i] = (Bk[i - 1] * B).mod_xk(n);
		}
		poly Bqk(1);
		poly ans;
		for (int i = 0; i <= n / q; i++) {
			poly cur;
			for (int j = 0; j < q; j++) {
				cur += Bk[j] * A[i * q + j];
			}
			ans += (Bqk * cur).mod_xk(n);
			Bqk = (Bqk * Bq).mod_xk(n);
		}
		return ans;
	}

	vector<T> eval(vector<poly> &tree, int v, int l, int r, vector<T> &vec) { // auxiliary evaluation function
		if (r - l == 1) {
			return {eval(vec[l])};
		} else {
			auto m = l + (r - l) / 2;
			auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, m, vec);
			auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1, m, r, vec);
			A.insert(end(A), begin(B), end(B));
			return A;
		}
	}

	vector<T> eval(vector<T> x) { // evaluate polynomial in (x1, ..., xn)
		int n = x.size();
		if (is_zero()) {
			return vector<T>(n, T(0));
		}
		vector<poly> tree(4 * n);
		build(tree, 1, 0, sz(x), x);
		return eval(tree, 1, 0, sz(x), x);
	}

	poly inter(vector<poly> &tree, int v, int l, int r, int ly, int ry, vector<T> &vecx, vector<T> &vecy) { // auxiliary interpolation function
		if (r - l == 1) {
			return {vecy[ly] / a[0]};
		} else {
			auto m = l + (r - l) / 2;
			auto my = ly + (ry - ly) / 2;
			auto A = (*this % tree[2 * v]).inter(tree, 2 * v, l, m, ly, my, vecx, vecy);
			auto B = (*this % tree[2 * v + 1]).inter(tree, 2 * v + 1, m, r, my, ry, vecx, vecy);
			return A * tree[2 * v + 1] + B * tree[2 * v];
		}
	}

	static poly build(vector<poly> &res, int v, int L, int R, vector<T> &vec) { // builds evaluation tree for (x-a1)(x-a2)...(x-an)
		if (R - L == 1) {
			return res[v] = vector<T>{-vec[L], 1};
		} else {
			int M = L + (R - L) / 2;
			return res[v] = build(res, 2 * v, L, M, vec) * build(res, 2 * v + 1, M, R, vec);
		}
	}

	static poly inter(vector<T> x, vector<T> y) { // interpolates minimum polynomial from (xi, yi) pairs
		int n = x.size();
		vector<poly> tree(4 * n);
		return build(tree, 1, 0, sz(x), x).deriv().inter(tree, 1, 0, sz(x), 0, sz(y), x, y);
	}
};

using polyn = poly<mint>;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<mint> x(n), y(n);
	for (auto &v : x)
		cin >> v.val;
	for (auto &v : y)
		cin >> v.val;
	polyn::inter(x, y).print(n);
}