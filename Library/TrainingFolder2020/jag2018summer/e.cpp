#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 500005;
const int mod = 1e9 + 7;

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

int n;
char str[MAXN];

bool hasfour(){
	vector<lint> v(n);
	for(int i=0; i<n; i++) v[i] = (str[i] == '1');
	v[0] = 0;
	vector<lint> w = multiply(v, v);
	for(int i=0; i<n; i++){
		if(w[i] && str[i] == '1'){
			if(w[i] == 1 && i % 2 == 0 && v[i / 2]) continue;
			return 1;
		}
	}
	return 0;
}

bool sex(vector<int> v){
	sort(all(v));
	for(auto &i : v){
		for(auto &j : v){
			if(
				binary_search(all(v), i+j) ||
				binary_search(all(v), abs(i-j))) continue;
				return 0;
		}
	}
	return 1;
}

int main(){
	scanf("%s", str);
	n = strlen(str);
	if(str[0] == '0'){
		puts("0");
		return 0;
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		int fuck = 1;
		for(int j=i; j<n; j+=i){
			if(str[j] == '0'){
				break;
			}
			else fuck++;
		}
		ret = max(ret, fuck);
	}
	if(hasfour()) ret = max(ret, 4);
	cout << ret << endl;
}
