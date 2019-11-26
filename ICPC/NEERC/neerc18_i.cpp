#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 405;

int q, mod;
lint ans[MAXN], dp[MAXN][MAXN], fact[MAXN], nofix[MAXN];

int main(){
	cin >> q >> mod;
	fact[0] = 1;
	dp[0][0] = 1;
	for(int i=1; i<MAXN; i++) fact[i] = fact[i-1] * i % mod;
	for(int i=1; i<MAXN; i++){
		for(int j=0; j<MAXN; j++){
			for(int k=1; k<=j; k++){
				dp[i][j] += dp[i-1][j-k] * fact[k] % mod;
			}
			dp[i][j] %= mod;
		}
	}
	for(int i=1; i<MAXN; i++){
		ans[i] = fact[i];
		nofix[i] = fact[i];
		for(int j=3; j<i; j++){
			ans[i] += mod - ans[j] * dp[j][i] % mod;
		}
		for(int j=1; j<i; j++){
			nofix[i] += mod - nofix[j] * fact[i - j] % mod;
			if(i > 2) ans[i] += mod - (2 * nofix[j] * fact[i - j]) % mod;
		}
		ans[i] %= mod;
		nofix[i] %= mod;
	}
	while(q--){
		int x; cin >> x; cout << ans[x] << endl;
	}
}
