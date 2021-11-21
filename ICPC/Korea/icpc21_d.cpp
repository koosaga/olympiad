#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1005;

int n, m;
int adj[MAXN][MAXN], col[MAXN], cnt[2];

void dfs(int x, int c){
	if(col[x]){
		if(col[x] != c){
			cout << "-1\n"; exit(0);
		}
		return;
	}
	col[x] = c;
	cnt[col[x] - 1]++;
	for(int i = 1; i <= n; i++){
		if(x != i && adj[x][i] == 0) dfs(i, 3 - c);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int s, e; cin >> s >> e;
		adj[s][e] = adj[e][s] = 1;
	}
	bitset<MAXN> dp = 1;
	for(int i = 1; i <= n; i++){
		if(!col[i]){
			cnt[0] = cnt[1] = 0;
			dfs(i, 1);
			dp = (dp << cnt[0]) | (dp << cnt[1]);
		}
	}
	int ans = 1e9;
	for(int i = 0; i <= n; i++){
		if(dp[i]) ans = min(ans, abs(n - 2 * i));
	}
	cout << ans << endl;
}
