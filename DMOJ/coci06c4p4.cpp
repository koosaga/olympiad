// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c4p4
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 1001;
const ll MAXC = 10001;
const ll MOD = 1e9 + 7;
ll dp[2][MAXC];
ll somatorio[MAXC];
int main(){
	ll n,k;
	scanf("%lld %lld",&n,&k);
	dp[1][0] = 1;dp[1][1] = 0;
	for(ll vez = 2;vez<=n;vez++){
		for(ll i = 0;i<=k;i++){
			dp[0][i] = dp[1][i];
			somatorio[i] = dp[0][i];
			dp[1][i] = 0;
		}
		for(ll i = 1;i<=k;i++){
			somatorio[i] += somatorio[i-1];
			somatorio[i] %= MOD;
		}
		for(ll i = 0;i<=k;i++){
			ll hi = i;
			ll lo = i - min(i,vez-1);
			ll val = somatorio[hi];
			if(lo != 0) val -= somatorio[lo - 1];
			val %= MOD;
			dp[1][i] = val;
		}
		for(ll i = (vez*(vez-1))/2 + 1;i<=k;i++){
			dp[1][i] = 0;
		}
	}
	ll exibir = dp[1][k] % MOD;
	if(exibir < 0) exibir += MOD;
	printf("%lld\n",exibir);
	return 0;
}