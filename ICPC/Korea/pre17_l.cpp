#include <bits/stdc++.h>
using namespace std;
using lint = long long;

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
		int n = 2; while(n < v.size() + w.size()) n <<= 1;
		fv.resize(n); fw.resize(n);
		fft(fv, 0); fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++) ret[i] = (lint)round(fv[i].real());
		return ret;
	}
};

vector<vector<lint>> a, b;

int main(){
	int n, m, q;
	lint w;
	scanf("%d %d %d %lld",&n,&m,&q,&w);
	a.resize(q); b.resize(q);
	vector<lint> v(n - m + 1);
	for(int i=0; i<q; i++){
		a[i].resize(n);
		for(int j=0; j<n; j++){
			scanf("%lld",&a[i][j]);
		}
	}
	for(int i=0; i<q; i++){
		b[i].resize(m);
		for(int j=0; j<m; j++){
			scanf("%lld",&b[i][m-j-1]);
		}
	}
	for(int i=0; i<q; i++){
		auto x = fft::multiply(a[i], b[i]);
		for(int j=m-1; j<n; j++){
			v[j-(m-1)] += x[j];
		}
	}
	int cnt = 0;
	for(auto &i : v){
		if(i > w) cnt++;
	}
	cout << cnt << endl;
}
