#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

lint fact[MAXN], invf[MAXN];

lint bino(int x, int y){
	return fact[x] * (invf[y] * invf[x-y] % mod) % mod;
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
	int n, k;
	cin >> n >> k;
	k--;
	fact[0] = invf[0] = 1;
	for(int i=1; i<=n+1; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	lint ans = 0;
	for(int i=0; i<=k; i++) ans += (i % 2 ? -1 : 1) * bino(n+1, i) * ipow(k - i + 1, n) % mod;
	ans = ((ans % mod) + mod) % mod;
	cout << ans << endl;
}

