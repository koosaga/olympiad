#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

lint dp[2][90005];
lint nxt[2][90005];

lint ipow(int x, int c){
	lint ans = 1;
	for(int i=0; i<c; i++) ans = (ans * x ) % mod;
	return ans;
}

int main(){
	int n; cin >> n;
	int sum = 0;
	dp[0][0] = 1;
	for(int i=0; i<n; i++){
		int x;
		cin >> x;
		memset(nxt, 0, sizeof(nxt));
		for(int i=0; i<=sum; i++){
			nxt[0][i] += dp[0][i];
			nxt[1][i] += dp[1][i];
			nxt[0][i + x] += dp[1][i];
			nxt[1][i + x] += dp[0][i];
		}
		memcpy(dp, nxt, sizeof(dp));
		sum += x;
		for(int i=0; i<2; i++){
			for(int j=0; j<=sum; j++) dp[i][j] %= mod;
		}
	}
	lint ans = 0;
	int s;
	cin >> s;
	for(int i=0; i<s; i++){
		int pwr = ipow(s - i, n);
		ans += 1ll * dp[0][i] * pwr;
		ans -= 1ll * dp[1][i] * pwr;
		ans += mod;
		ans %= mod;
	}
	cout << ans % mod;
}
