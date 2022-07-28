#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 1005;

vector<int> gph[MAXN];
pi sol;
int vis[MAXN], dfn[MAXN], low[MAXN], sz[MAXN], piv;
int chk[MAXN];

void dfs(int x, int p = -1){
	dfn[x] = low[x] = ++piv;
	vis[x] = 1;
	sz[x] = 1;
	for(auto &y : gph[x]){
		if(y == p || chk[y]) continue;
		if(!dfn[y]){
			dfs(y, x);
			sz[x] += sz[y];
			low[x] = min(low[x], low[y]);
			if(low[y] > dfn[x] && sz[y] % 2) sol = pi(min(x, y), max(x, y));
		}
		else low[x] = min(low[x], dfn[y]);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int tc; cin >> tc;
	while(tc--){
		memset(chk, 0, sizeof(chk));
		int n, m; cin >> n >> m;
		for(int i = 0; i < m; i++){
			int s, e; cin >> s >> e;
			s--; e--;
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
		vector<pi> v;
		for(int i = 0; i < n / 2; i++){
			memset(vis, 0, sizeof(vis));
			memset(dfn, 0, sizeof(dfn));
			sol = pi(-1, -1);
			for(int j = 0; j < n; j++){
				if(!chk[j] && !vis[j]){
					dfs(j);
					if(sz[j] % 2) sol = pi(-1, -1);
					if(sol != pi(-1, -1)) break;
				}
			}
			if(sol == pi(-1, -1)){
				cout << "NO\n";
				break;
			}
			chk[sol.first] = 1;
			chk[sol.second] = 1;
			v.push_back(sol);
		}
		if(sz(v) == n / 2){
			cout << "YES\n";
			sort(all(v));
			for(auto &[x, y] : v) cout << x+1 << " " << y+1 << "\n";
		}
		for(int i = 0; i < n; i++) gph[i].clear();
	}
}
