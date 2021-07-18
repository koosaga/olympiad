#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 100005;

int dp[1 << 10], n, a[10];

void solve(){
	cin >> n;
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 1; i < (1<<n); i++){
		dp[i] = 1e9;
		for(int j = i; j; j = (j - 1) & i){
			for(int k = 0; k < n; k++){
				if((j >> k) & 1){
					dp[i] = min(dp[i], max(dp[j - (1<<k)] + a[k], 1 + dp[i - j]));
				}
			}
		}

	}
	cout << dp[(1<<n) - 2] + a[0] << endl;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}
