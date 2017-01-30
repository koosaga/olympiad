#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 33;

lint fact[100005], invf[1000005];
lint dp[100005];

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p&1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret;
}

int n, k, a[505];

int main(){
	cin >> n >> k;
	for(int i=0; i<k; i++) cin >> a[i];
	dp[0] = 1;
	fact[0] = 1;
	for(int i=1; i<=n; i++){
		fact[i] = fact[i-1] * i % mod;
	}
	lint sum = 1;
	for(int i=1; i<=n; i++){
		dp[i] = sum;
		for(int j=0; j<k; j++){
			if(i >= a[j]){
				dp[i] += mod - dp[i-a[j]];
				dp[i] %= mod;
			}
		}
		dp[i] *= ipow(i, mod-2);
		dp[i] %= mod;
		sum += dp[i];
		dp[i] %= mod;
	}
	cout << dp[n] * fact[n] % mod;
}
