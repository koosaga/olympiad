#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 3005;

int dp[MAXN][MAXN][2];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	vector<lint> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i], a[i] ^= a[i-1];
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= n; j++){
			for(int k = 0; k < 2; k++){
				dp[i][j][k] = -1e9;
			}
		}
	}
	for(int i = 1; i <= n; i++){
		dp[1][i][0] = dp[1][i][1] = 1;
	}
	for(int i = 1; i < n; i++){
		// [j, i] x [i+1, k]
		vector<pi> L, R;

		for(int j = 1; j <= i; j++){
			L.push_back({a[j-1] ^ a[i], j});
		}
		for(int k = i + 1; k <= n; k++){
			R.push_back({a[k] ^ a[i], k});
		}
		sort(all(L));
		sort(all(R));
		{
			int j = 0, curMax = -1e9;
			for(auto &[val, k] : R){
				while(j < sz(L) && L[j].first < val){
					curMax = max(curMax, dp[L[j].second][i][0] + 1);
					j++;
				}
				dp[i + 1][k][1] = max(dp[i+1][k][1], curMax);
			}
		}
		reverse(all(L));
		reverse(all(R));
		{
			int j = 0, curMax = -1e9;
			for(auto &[val, k] : R){
				while(j < sz(L) && L[j].first > val){
					curMax = max(curMax, dp[L[j].second][i][1] + 1);
					j++;
				}
				dp[i + 1][k][0] = max(dp[i+1][k][0], curMax);
			}
		}
	}
	int ans = min(2, n);
	for(int i = 1; i <= n; i++){
		ans = max({ans, dp[i][n][0], dp[i][n][1]});
	}
	cout << n - ans << "\n";
}
