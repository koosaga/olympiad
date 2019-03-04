#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<llf, llf> pi;
const int mod = 1e9 + 7;
const llf eps = 1e-11;

namespace fft{
	typedef complex<double> base;
	void fft(vector<base> &v, bool inv){
		int n = v.size();
		vector<base> w(n/2), aux(n);
		for(int i=0; i<n/2; i++){
			int k = i & -i;
			if(i == k){
				double ang = 2 * M_PI * i / n;
				if(inv) ang *= -1;
				w[i] = base(cos(ang), sin(ang));
			}
			else w[i] = w[i-k] * w[k];
		}
		for(int i=n/2; i; i>>=1){
			aux = v;
			for(int k=0; 2*k<n; k+=i){
				for(int j=0; j<i; j++){
					base a = aux[2 * k + j];
					base b = aux[2 * k + j + i] * w[k];
					v[k + j] = a + b;
					v[k + j + n/2] = a - b;
				}
			}
		}
		if(inv){
			for(int i=0; i<n; i++) v[i] /= n;
		}
	}
	vector<lint> multiply(vector<lint> &v, vector<lint> &w){
		vector<base> fv(v.begin(), v.end());
		vector<base> fw(w.begin(), w.end());
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		fv.resize(n);
		fw.resize(n);
		fft(fv, 0); fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
}

vector<lint> a, b;
char str[1000005];
int n;

int main(){
	scanf("%s", str);
	n = strlen(str);
	a.resize(n); b.resize(n);
	for(int i=0; i<n; i++){
		if(str[i] == 'A') a[i] = 1;
		else b[n-1-i] = 1;
	}
	auto x = fft::multiply(a, b);
	for(int i=n; i<=2*n-2; i++) printf("%lld\n", x[i]);
}

