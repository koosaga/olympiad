#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
typedef complex<double> base;

namespace fft{
	typedef complex<double> base;
	void fft(vector<base> &a, bool invert){
		int n = a.size();
		for (int i=1,j=0;i<n;i++){
			int bit = n >> 1;
			for (;j>=bit;bit>>=1) j -= bit;
			j += bit;
			if (i < j) swap(a[i],a[j]);
		}
		for (int len=2;len<=n;len<<=1){
			double ang = 2*M_PI/len*(invert?-1:1);
			base wlen(cos(ang),sin(ang));
			for (int i=0;i<n;i+=len){
				base w(1);
				for (int j=0;j<len/2;j++){
					base u = a[i+j], v = a[i+j+len/2]*w;
					a[i+j] = u+v;
					a[i+j+len/2] = u-v;
					w *= wlen;
				}
			}
		}
		if (invert){
			for (int i=0;i<n;i++) a[i] /= n;
		}
	}
	void fft_koosaga(vector<base> &v, bool inv){
		vector<base> w(v.size());
		for(int i=2; i<=v.size(); i<<=1){
			int bsz = v.size() / i;
			base ang(cos(2 * M_PI / i), sin(2 * M_PI / i));
			if(inv) ang = base(1, 0) / ang;
			for(int j=0; j<bsz; j++){
				for(int k=0; k<i; k++){
					w[k] = v[bsz * k + j];
				}
				base pw(1, 0);
				for(int k=0; k<i/2; k++){
					base a = w[2*k], b = w[2*k+1] * pw;
					v[bsz * k + j] = a + b;
					v[bsz * k + j + v.size()/2] = a - b;
					pw *= ang;
				}
			}
		}
		if(inv){
			for(int i=0; i<v.size(); i++){
				v[i] /= v.size();
			}
		}
	}
	vector<int> multiply(vector<int> &v, vector<int> &w){
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
		vector<int> ret(n);
		for(int i=0; i<n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
	vector<int> power(vector<int> &v){
		vector<base> fv(v.begin(), v.end());
		int n = 1;
		while(n < v.size()) n <<= 1;
		n <<= 1;
		fv.resize(n);
		fft(fv, 0);
		for(int i=0; i<n; i++) fv[i] *= fv[i];
		fft(fv, 1);
		vector<int> ret(n);
		for(int i=0; i<n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
};

int main(){
	vector<int> v(500001);
	for(int i=1; i<=500000; i++){
		for(int j=i; j<=500000; j+=i){
			v[j]++;
		}
	}
	auto ret = fft::power(v);
	int t;
	scanf("%d",&t);
	while(t--){
		int s, e;
		scanf("%d %d",&s,&e);
		int pos = -1, retv = -1;
		for(int i=s; i<=e; i++){
			if(retv < ret[i]){
				retv = ret[i];
				pos = i;
			}
		}
		printf("%d %d\n",pos,retv);
	}
}


