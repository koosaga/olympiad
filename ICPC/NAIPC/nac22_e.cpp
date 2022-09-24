#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 5005;
const int MAXV = 10005;

vector<int> gph[MAXN];
int a[MAXN], n, dp[MAXN][MAXV];
vector<int> pf[MAXV];

void dfs(int x, int p){
	for(auto &y : gph[x]){
		if(y == p) continue;
		dfs(y, x);
		for(int a = 2; a < MAXV; a++){
			int toAdj = 1e9;
			for(auto &b : pf[a]){
				toAdj = min(toAdj, dp[y][b]);
			}
			dp[x][a] += toAdj;
		}
	}
	for(int i = 2; i < MAXV; i++){
		if(i != a[x]) dp[x][i] += i;
	}
	for(int i = 2; i < MAXV; i++){
		for(int j = 2 * i; j < MAXV; j += i) dp[x][i] = min(dp[x][i], dp[x][j]);
	}
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 2; i < MAXV; i++){
		int cur = i;
		for(int j = 2; j * j <= cur; j++){
			if(cur % j == 0) pf[i].push_back(j);
			while(cur % j == 0){
				cur /= j;
			}
		}
		if(cur > 1) pf[i].push_back(cur);
	}
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 0; i < n - 1; i++){
		int u, v; cin >> u >> v;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(1, 0);
	cout << *min_element(dp[1] + 2, dp[1] + MAXV) << "\n";
}
