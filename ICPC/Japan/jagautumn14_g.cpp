#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;
const int MAXN = 2005;

int n, x; lint d;
int bino[MAXN][MAXN];
lint dcn[MAXN];

lint solve(int n, lint d, int x){
	if(n < 0) return 0;
	if(n == 0) return dcn[x];
	lint ret = 0;
	for(int i=1; i<=n; i++){
		ret += (dcn[i] * dcn[x] % mod) * bino[n-1][i-1] % mod;
	}
	return ret % mod;
}

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int main(){
	for(int i=0; i<MAXN; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++) bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % mod;
	}
	while(true){
		cin >> n >> d >> x;
		if(d == 0) break;
		if(x == 1){
			cout << 0 << endl;
			continue;
		}
		memset(dcn, 0, sizeof(dcn));
		dcn[0] = 1;
		for(int i=1; i<MAXN && i <= d+1; i++){
			dcn[i] = dcn[i-1] * (((d + 1 - i) % mod) * ipow(i, mod - 2) % mod) % mod;
		}
		lint ret = 0;
		for(int i=0; i<n; i++){
			if(i % 2 == 0) ret += solve(n - i * x, d, i);
			else ret += mod - solve(n - i * x, d, i);
		}
		cout << ret%mod << endl;
	}
}
