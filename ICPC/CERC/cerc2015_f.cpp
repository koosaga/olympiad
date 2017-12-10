#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e6 + 3;
const int MAXN = 400005;

namespace fft{
	typedef complex<double> base;
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
		if(inv) for(int i=0; i<n; i++) a[i] /= n;
	}

	vector<lint> multiply(vector<lint> &v, vector<lint> &w){
		vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		fv.resize(n);
		fw.resize(n);
		fft(fv, 0);
		fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++) ret[i] = (lint)round(fv[i].real());
		return ret;
	}
	vector<lint> multiply(vector<lint> &v, vector<lint> &w, lint mod){
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		vector<base> v1(n), v2(n);
		vector<base> r1(n), r2(n);
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
		vector<lint> ret(n);
		for(int i=0; i<n; i++){
			lint av = (lint)round(r1[i].real());
			lint bv = (lint)round(r1[i].imag()) + (lint)round(r2[i].real());
			lint cv = (lint)round(r2[i].imag());
			av %= mod, bv %= mod, cv %= mod;
			ret[i] = (av << 30) + (bv << 15) + cv;
			ret[i] %= mod;
			ret[i] += mod;
			ret[i] %= mod;
		}
		return ret;
	}
}


lint ipow(lint x, lint p){
	lint ret = 1, piv = x % mod;
	while(p){
		if(p&1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret % mod;
}

lint fact[MAXN], invf[MAXN];
int n, a, b, c;
int l[MAXN], t[MAXN];

lint bino(int x, int y){
	return fact[x+y] * (invf[x] * invf[y] % mod) % mod;
}

int main(){
	fact[0] = invf[0] = 1;
	for(int i=1; i<MAXN; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod-2);
	}
	int n, a, b, c;
	scanf("%d %d %d %d",&n,&a,&b,&c);
	lint ans = 0;
	int x;
	for(int i=1; i<=n; i++){
		scanf("%d",&x);
		if(i > 1) ans += 1ll * x * bino(n-2, n-i) * (ipow(a, n-1) * ipow(b, n-i) % mod) % mod;
	}
	for(int i=1; i<=n; i++){
		scanf("%d",&x);
		if(i > 1) ans += 1ll * x * bino(n-2, n-i) * (ipow(a, n-i) * ipow(b, n-1) % mod) % mod;
	}
	vector<lint> p1(n-1), p2(n-1);
	for(int i=0; i<=n-2; i++){
		p1[i] = ipow(a, i) * invf[i] % mod;
		p2[i] = ipow(b, i) * invf[i] % mod;
	}
	auto ret = fft::multiply(p1, p2, mod);
	for(int i=0; i<=2*n-4; i++){
		ans += fact[i] * ret[i] * c % mod;
	}
	cout << ans % mod;
}
