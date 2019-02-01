#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

namespace FFT{
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
		/* In NTT, let prr = primitive root. Then,
		   int ang = ipow(prr, (mod - 1) / n);
		   if(inv) ang = ipow(ang, mod - 2);
		   for(int i=0; i<n/2; i++){
		   roots[i] = (i ? (1ll * roots[i-1] * ang % mod) : 1);
		   }
		   Others are same. If there is /= n, do *= ipow(n, mod - 2).
		   In XOR convolution, roots[*] = 1.
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
		if(inv) for(int i=0; i<n; i++) a[i] /= n;
	}

	vector<int> multiply(vector<int> &v, vector<int> &w){
		vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
		int n = 2; while(n < v.size() + w.size()) n <<= 1;
		fv.resize(n); fw.resize(n);
		fft(fv, 0); fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<int> ret(n);
		for(int i=0; i<n; i++) ret[i] = (int)round(fv[i].real());
		return ret;
	}
}

int n, m;
char str1[MAXN], str2[MAXN];
int dap[MAXN];

void Do(char x, char y){
	vector<int> a(n), b(m);
	for(int i=0; i<n; i++) a[i] = (str1[i] == x);
	for(int i=0; i<m; i++) b[m-1-i] = (str2[i] == y);
	auto ans = FFT::multiply(a, b);
	for(int i=m-1; i<n+m-1; i++) dap[i-m+1] += ans[i];
}

int main(){
	scanf("%d %d %s %s",&n,&m,str1,str2);
	Do('R', 'P');
	Do('P', 'S');
	Do('S', 'R');
	cout << *max_element(dap, dap + n) << endl;
}
