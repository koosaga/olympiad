#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 15005;

vector<pi> gph[MAXN];
int dp[MAXN];

int main(){
	int n, m; cin >> n >> m;
	vector<int> a(n + 1);
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=0; i<m; i++){
		int s, e, x; cin >> s >> e >> x;
		gph[s].emplace_back(e, a[x] * (e - s));
	}
	for(int i=0; i<MAXN-1; i++){
		dp[i + 1] = max(dp[i], dp[i + 1]);
		for(auto &[x, y] : gph[i]){
			dp[x] = max(dp[x], dp[i] + y);
		}
	}
	cout << dp[MAXN - 1] << endl;
}
