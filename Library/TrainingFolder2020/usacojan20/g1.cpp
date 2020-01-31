#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int n, m, c;
int dp[MAXN][MAXN];
int a[MAXN];
vector<int> gph[MAXN];

int main(){
	freopen("time.in", "r", stdin);
	freopen("time.out", "w", stdout);
	cin >> n >> m >> c;
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=0; i<m; i++){
		int s, e; cin >> s >> e;
		gph[s].push_back(e);
	}
	for(int i=0; i<MAXN; i++){
		for(int j=0; j<MAXN; j++){
			dp[i][j] = -1e9;
		}
	}
	dp[0][1] = 0;
	int ans = 0;
	for(int i=0; i<1000; i++){
		for(int j=1; j<=n; j++){
			dp[i][j] += a[j];
			for(auto &k : gph[j]){
				dp[i + 1][k] = max(dp[i + 1][k], dp[i][j]);
			}
		}
		ans = max(ans, dp[i][1] - c * i * i);
	}
	cout << ans << endl;
}
