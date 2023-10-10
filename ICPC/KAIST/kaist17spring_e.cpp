#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

void fft(vector<lint> &a, bool inv){
	int n = a.size(), j = 0;
	for(int i=1; i<n; i++){
		int bit = (n >> 1);
		while(j >= bit){
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}
	for(int i=2; i<=n; i<<=1){
		int step = n / i;
		for(int j=0; j<n; j+=i){
			for(int k=0; k<i/2; k++){
				lint u = a[j+k], v = a[j+k+i/2];
				a[j+k] = u+v;
				a[j+k+i/2] = u-v;
			}
		}
	}
	if(inv) for(int i=0; i<n; i++) a[i] = a[i] / n;
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	vector<lint> cnt(1<<19), v(1<<19);
	for(int i=1; i<=n; i++){
		lint x;
		scanf("%lld",&x);
		x %= (m+1);
		cnt[x]++;
	}
	v = cnt;
	fft(v, 0);
	for(auto &i : v) i = i * i;
	fft(v, 1);
	lint ret = 0;
	for(int i=0; i<(1<<19); i++){
		ret += v[i] * cnt[i];
	}
	ret -= 3ll * cnt[0] * n;
	ret += 2ll * cnt[0];
	assert(ret % 6 == 0);
	printf("%lld", ret / 6);
}
