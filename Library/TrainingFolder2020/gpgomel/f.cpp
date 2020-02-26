#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 998244353;

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int n, m;
lint fact[MAXN], invf[MAXN], invp[MAXN];

lint bino(int x, int y){
	if(x < y) return 0;
	return fact[x] * (invf[y] * invf[x - y] % mod) % mod;
}

lint fsum[105][MAXN];
lint gsum[105][MAXN];
bool chk[MAXN];
lint solve(vector<int> v){
	if(sz(v) > 100){
		for(auto &i : v) chk[i] = 1;
		lint ret = 0;
		int ptr = 0;
		for(int i=n; i<2*n; i++){
			while(ptr < sz(v) && v[ptr] < i) ptr++;
			int fixed = ptr + 1;
			if(!chk[i]) ret += bino(i - fixed, n - 1) * invp[i];
			if(v.back() <= i) ret += bino(i - fixed, i - n) * invp[i];
			ret %= mod;
		}
		for(auto &i : v) chk[i] = 0;
		return (2 * ret) % mod;
	}
	else{
		auto proc = [&](int l, int r, int fixed){
			if(l > r) return 0ll;
			return fsum[fixed][r] - fsum[fixed][l - 1] + mod;
		};
		lint ret = proc(n, v[0] - 1, 1);
		for(int i=0; i<sz(v); i++){
			int st = max(n, v[i] + 1);
			int ed = (i + 1 < sz(v) ? v[i + 1] : (2*n));
			ret += proc(st, ed - 1, i + 2);
		}
		if(v.back() >= n && v.back() <= 2 * n - 1){
			int i = v.back();
			ret += bino(i - sz(v), i - n) * invp[i];
		}
		int st = v.back() + 1;
		int ed = 2 * n - 1;
		st = max(st, n);
		if(st <= ed){
			ret += gsum[sz(v) + 1][ed] - gsum[sz(v) + 1][st - 1] + mod;
		}
		ret %= mod;
		return (2 * ret) % mod;
	}
}

int main(){
	fact[0] = invf[0] = invp[0] = 1;
	for(int i=1; i<MAXN; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
		invp[i] = invp[i-1] * ((mod + 1) / 2) % mod;
	}
	scanf("%d %d",&n,&m);
	for(int i=0; i<105; i++){
		for(int j=n; j<=2*n; j++){
			fsum[i][j] = bino(j - i, n - 1) * invp[j] + fsum[i][j-1];
			fsum[i][j] %= mod;
			gsum[i][j] = bino(j - i, j - n) * invp[j] + gsum[i][j-1];
			gsum[i][j] %= mod;
		}
	}
	while(m--){
		int k;
		scanf("%d",&k);
		vector<int> v(k);
		for(auto &i : v) scanf("%d",&i);
		printf("%lld\n", solve(v));
	}
}
