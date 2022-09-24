#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;

struct edge{
	int idx, day, to;
	bool operator<(const edge &e)const{
		return e.day < day;
	};
};

vector<edge> gph[MAXN];
int n, k, m;

bool vis[MAXN][15], chk[MAXN];

void dfs(int x, int d){
	if(vis[x][d]) return;
	vis[x][d] = 1;
	for(auto &y : gph[x]){
		if(!chk[y.idx] && y.day == d) dfs(y.to, d + 1);
	}
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k >> m;
	for(int i = 0; i < m; i++){
		int u, v, x; cin >> u >> v >> x;
		gph[u].push_back({i, x, v});
		gph[v].push_back({i, x, u});
	}
	for(int i = 1; i <= n; i++){
		gph[0].push_back({i+m-1, 0, i});
		gph[i].push_back({i+m-1, 0, 0});
	}
	for(int i = 1; i <= n; i++){
		sort(all(gph[i]));
		int p = 0;
		while(p < sz(gph[i]) && gph[i][p].day >= gph[i][0].day - 1) p++;
		for(int j = p; j < sz(gph[i]); j++) chk[gph[i][j].idx] = 1;
	}
	for(int i = 1; i <= n; i++){
		if(gph[i][0].day == 1) dfs(i, 1);
	}
	vector<int> v;
	for(int i = 1; i <= n; i++){
		if(vis[i][k+1]) v.push_back(i);
	}
	cout << sz(v) << endl;
	for(auto &x : v) cout << x << endl;
		
}

