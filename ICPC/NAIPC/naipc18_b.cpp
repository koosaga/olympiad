#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int mod = 1e9 + 7;
using lint = long long;

int n, m, deg[MAXN], lo[MAXN], hi[MAXN];
lint fact[MAXN], invf[MAXN];

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

lint binom(int x, int y){
	return fact[x] * (invf[y] * invf[x - y] % mod) % mod;
}

int main(){
	fact[0] = invf[0] = 1;
	for(int i=1; i<MAXN; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	scanf("%d %d",&n,&m);
	while(m--){
		int x, y; scanf("%d %d",&x,&y);
		x--, y--;
		deg[x]++;
		deg[y]++;
	}
	sort(deg, deg + n);
	int tot = accumulate(deg, deg + n, 0);
	memset(lo, 0x3f, sizeof(lo));
	for(int i=0; i<n; i++){
		lo[deg[i]] = min(lo[deg[i]], i);
		hi[deg[i]] = max(hi[deg[i]], i);
	}
	int l = 0, r = tot;
	lint ans = 0;
    if(r - l == 1ll * n * (n - 1)) ans++;
	for(int i=0; i<n; i++){
		l += deg[i];
		r -= deg[i];
		if(r - l == 1ll * (n - i - 1) * (n - i - 2)){
			int totcnt = hi[deg[i]] - lo[deg[i]] + 1;
			int partcnt = i - lo[deg[i]] + 1;
			ans += binom(totcnt, partcnt);
		}
	}
	ans %= mod;
	cout << ans << endl;
}

