#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
const int mod = 998244353;

template<typename T>
T gcd(const T &a, const T &b) {
	return b == T(0) ? a : gcd(b, a % b);
}

struct mint {
	int val;
	mint() { val = 0; }
	mint(const lint& v) {
		val = (-mod <= v && v < mod) ? v : v % mod;
		if (val < 0) val += mod;
	}

	friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
	friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
	friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
	friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }

	mint operator-() const { return mint(-val); }
	mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
	mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
	mint& operator*=(const mint& m) { val = (lint)val*m.val%mod; return *this; }
	friend mint ipow(mint a, lint p) {
		mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans;
	}
	friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
	mint& operator/=(const mint& m) { return (*this) *= inv(m); }

	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
	operator int64_t() const {return val; }
};

namespace fft{
	using base = complex<double>;

	void fft(vector<base> &a, bool inv){
		int n = a.size(), j = 0;
		vector<base> roots(n/2);
		for(int i=1; i<n; i++){
			int bit = (n >> 1);
			while(j >= bit){
				j -= bit;
				bit >>= 1;
			}
			j += bit;
			if(i < j) swap(a[i], a[j]);
		}
		double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
		for(int i=0; i<n/2; i++){
			roots[i] = base(cos(ang * i), sin(ang * i));
		}
		/*
		   XOR Convolution : set roots[*] = 1.
		   OR Convolution : set roots[*] = 1, and do following:
		   if (!inv) {
		   a[j + k] = u + v;
		   a[j + k + i/2] = u;
		   } else {
		   a[j + k] = v;
		   a[j + k + i/2] = u - v;
		   }
		 */
		for(int i=2; i<=n; i<<=1){
			int step = n / i;
			for(int j=0; j<n; j+=i){
				for(int k=0; k<i/2; k++){
					base u = a[j+k], v = a[j+k+i/2] * roots[step * k];
					a[j+k] = u+v;
					a[j+k+i/2] = u-v;
				}
			}
		}
		if(inv) for(int i=0; i<n; i++) a[i] /= n; // skip for OR convolution.
	}
	template<typename T>
	void ntt(vector<T> &a, bool inv){
		const int prr = 3; // primitive root
		int n = a.size(), j = 0;
		vector<T> roots(n/2);
		for(int i=1; i<n; i++){
			int bit = (n >> 1);
			while(j >= bit){
				j -= bit;
				bit >>= 1;
			}
			j += bit;
			if(i < j) swap(a[i], a[j]);
		}
		T ang = ipow(T(prr), (mod - 1) / n);
		if(inv) ang = T(1) / ang;
		for(int i=0; i<n/2; i++){
			roots[i] = (i ? (roots[i-1] * ang) : T(1));
		}
		for(int i=2; i<=n; i<<=1){
			int step = n / i;
			for(int j=0; j<n; j+=i){
				for(int k=0; k<i/2; k++){
					T u = a[j+k], v = a[j+k+i/2] * roots[step * k];
					a[j+k] = u+v;
					a[j+k+i/2] = u-v;
				}
			}
		}
		if(inv){
			T rev = T(1) / T(n);
			for(int i=0; i<n; i++) a[i] *= rev;
		}
	}
	template<typename T>
	vector<T> multiply_ntt(vector<T> &v, const vector<T> &w){
		vector<T> fv(all(v)), fw(all(w));
		int n = 2;
		while(n < sz(v) + sz(w)) n <<= 1;
		fv.resize(n); fw.resize(n);
		ntt(fv, 0); ntt(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		ntt(fv, 1);
		vector<T> ret(n);
		for(int i=0; i<n; i++) ret[i] = fv[i];
		return ret;
	}
	template<typename T>
	vector<T> multiply(vector<T> &v, const vector<T> &w){
		vector<base> fv(all(v)), fw(all(w));
		int n = 2;
		while(n < sz(v) + sz(w)) n <<= 1;
		fv.resize(n); fw.resize(n);
		fft(fv, 0); fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<T> ret(n);
		for(int i=0; i<n; i++) ret[i] = (T)llround(fv[i].real());
		return ret;
	}
	template<typename T>
	vector<T> multiply_mod(vector<T> v, const vector<T> &w){
		int n = 2;
		while(n < sz(v) + sz(w)) n <<= 1;
		vector<base> v1(n), v2(n), r1(n), r2(n);
		for(int i=0; i<v.size(); i++){
			v1[i] = base(v[i] >> 15, v[i] & 32767);
		}
		for(int i=0; i<w.size(); i++){
			v2[i] = base(w[i] >> 15, w[i] & 32767);
		}
		fft(v1, 0);
		fft(v2, 0);
		for(int i=0; i<n; i++){
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
		for(int i=0; i<n; i++){
			T av = llround(r1[i].real());
			T bv = llround(r1[i].imag()) + llround(r2[i].real());
			T cv = llround(r2[i].imag());
			av = av << 30;
			bv = bv << 15;
			ret[i] = av + bv + cv;
		}
		return ret;
	}
}

template<typename T>
struct poly {
	vector<T> a;

	void normalize() { // get rid of leading zeroes
		while(!a.empty() && a.back() == T(0)) {
			a.pop_back();
		}
	}

	poly(){}
	poly(T a0){ a = {a0}; normalize(); }
	poly(vector<T> t) : a(t){ normalize(); }

	int deg() const{ return sz(a) - 1; } // -1 if empty

	T operator [](int idx) const {
		return idx >= (int)a.size() || idx < 0 ? T(0) : a[idx];
	}

	poly reversed() const{
		vector<T> b = a;
		reverse(all(b));
		return poly(b);
	}
	poly trim(int n) const{
		n = min(n, sz(a));
		vector<T> b(a.begin(), a.begin() + n);
		return poly(b);
	}

	poly operator *= (const T &x) {
		for(auto &it: a) {
			it *= x;
		}
		normalize();
		return *this;
	}
	poly operator /= (const T &x) {
		for(auto &it: a) {
			it /= x;
		}
		normalize();
		return *this;
	}
	poly operator * (const T &x) const {return poly(*this) *= x;}
	poly operator / (const T &x) const {return poly(*this) /= x;}

	poly operator+=(const poly &p){
		a.resize(max(sz(a), sz(p.a)));
		for(int i=0; i<sz(p.a); i++){
			a[i] += p.a[i];
		}
		normalize();
		return *this;
	}
	poly operator-=(const poly &p){
		a.resize(max(sz(a), sz(p.a)));
		for(int i=0; i<sz(p.a); i++){
			a[i] -= p.a[i];
		}
		normalize();
		return *this;
	}
	poly operator*=(const poly &p){
		// change multiplication method if needed
		*this = poly(fft::multiply_mod(a, p.a));
		normalize();
		return *this;
	}
	poly inv(int n){
		poly q(T(1) / a[0]);
		for(int i=1; i<n; i<<=1){
			q *= poly(2) - q * trim(i * 2);
			q = q.trim(i * 2);
		}
		return q.trim(n);
	}
	poly operator/=(const poly &b){
		if(deg() < b.deg()) return *this = poly();
		int k = deg() - b.deg() + 1;
		poly ra = reversed().trim(k);
		poly rb = b.reversed().trim(k).inv(k);
		*this = (ra * rb).trim(k);
		while(sz(a) < k) a.push_back(T(0));
		reverse(all(a));
		normalize();
		return *this;
	}
	poly operator%=(const poly &b){
		if(deg() < b.deg()) return *this;
		poly foo = poly(a); foo /= b; foo *= b;
		*this = poly(*this) -= foo;
		normalize();
		return *this;
	}

	poly operator+(const poly &p)const{ return poly(*this) += p; }
	poly operator-(const poly &p)const{ return poly(*this) -= p; }
	poly operator*(const poly &p)const{ return poly(*this) *= p; }
	poly operator/(const poly &p)const{ return poly(*this) /= p; }
	poly operator%(const poly &p)const{ return poly(*this) %= p; }
};