#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 205;

int n, m;
lint adj[MAXN][MAXN];
int trk[MAXN][MAXN];
lint dap[50005];

struct edg{
	int u, v, c, d, idx;
}ed[50005];

vector<int> pth;

void dfs(int x, int y){
	if(trk[x][y] <= 0) pth.push_back(-trk[x][y]);
	else{
		dfs(x, trk[x][y]);
		dfs(trk[x][y], y);
	}
}

bool chk[50005];
lint kek[MAXN][MAXN];

lint Do_rev(int i, int s, int t){
	memset(kek, 0x3f, sizeof(kek));
	for(int j=0; j<m; j++){
		int u = ed[j].u;
		int v = ed[j].v;
		lint c = ed[j].c;
		if(j != i) kek[u][v] = min(kek[u][v], c);
		else kek[v][u] = min(kek[v][u], c);
	}
	lint dist[MAXN];
	bool vis[MAXN] = {};
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	for(int i=0; i<n; i++){
		lint cur = 1e18;
		int pos = -1;
		for(int j=1; j<=n; j++){
			if(!vis[j] && dist[j] < cur){
				cur = dist[j];
				pos = j;
			}
		}
		if(pos == -1) break;
		vis[pos] = 1;
		for(int j=1; j<=n; j++){
			dist[j] = min(dist[pos] + kek[pos][j], dist[j]);
		}
	}
	return dist[t];
}

pi dist[2][MAXN][2]; // distance, which edge

void dijk(int s, int flag){
	bool vis[MAXN] = {};
	vector<edg> gph[MAXN];
	for(int i=0; i<m; i++){
		gph[ed[i].u].push_back(ed[i]);
	}
	dist[flag][s][0] = pi(0, 0);
	for(int i=0; i<n; i++){
		lint cur = 1e18;
		int pos = -1;
		for(int j=1; j<=n; j++){
			if(!vis[j] && dist[flag][j][0].first < cur){
				cur = dist[flag][j][0].first;
				pos = j;
			}
		}
		if(pos == -1) break;
		vis[pos] = 1;
		for(auto &j : gph[pos]){
			if(dist[flag][j.v][0].first > dist[flag][pos][0].first + j.c){
				dist[flag][j.v][0].first = dist[flag][pos][0].first + j.c;
				dist[flag][j.v][0].second = j.idx;
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(s == i){
			dist[flag][i][1].first = 0;
			continue;
		}
		dist[flag][i][1].first = Do_rev(dist[flag][i][0].second, s, i);
	}
}

void solve(int s, int t){
	memset(chk, 0, sizeof(chk));
	for(int i=0; i<2; i++){
		for(int j=0; j<MAXN; j++){
			for(int k=0; k<2; k++){
				dist[i][j][k] = pi(1e18, -1);
			}
		}
	}
	pth.clear();
	if(adj[s][t] < 1e17){
		dfs(s, t);
		for(int i=0; i<sz(pth); i++){
			chk[pth[i]] = 1;
		}
	}
	dijk(s, 0);
	for(int i=0; i<m; i++) swap(ed[i].u, ed[i].v);
	dijk(t, 1);
	for(int i=0; i<m; i++) swap(ed[i].u, ed[i].v);
	for(int i=0; i<m; i++){
		if(!chk[i]){
			lint foo = ed[i].c;
			if(dist[0][ed[i].v][0].second == i) foo += dist[0][ed[i].v][1].first;
			else foo += dist[0][ed[i].v][0].first;
			if(dist[1][ed[i].v][0].second == i) foo += dist[1][ed[i].u][1].first;
			else foo += dist[1][ed[i].u][0].first;
			dap[i] += min(adj[s][t], foo);
		}
		else{
			dap[i] += Do_rev(i, s, t);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	memset(adj, 0x1f, sizeof(adj));
	for(int i=1; i<=n; i++) adj[i][i] = 0;
	for(int i=0; i<m; i++){
		scanf("%d %d %d %d",&ed[i].u,&ed[i].v,&ed[i].c,&ed[i].d);
		ed[i].idx = i;
		if(adj[ed[i].u][ed[i].v] > ed[i].c){
			adj[ed[i].u][ed[i].v] = ed[i].c;
			trk[ed[i].u][ed[i].v] = -i;
		}
		dap[i] = ed[i].d;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				if(adj[j][k] > adj[j][i] + adj[i][k]){
					adj[j][k] = adj[j][i] + adj[i][k];
					trk[j][k] = i;
				}
			}
		}
	}
	lint ans = adj[1][n] + adj[n][1];
	solve(1, n);
	solve(n, 1);
	ans = min(ans, *min_element(dap, dap + m));
	if(ans > 1e15) ans = -1;
	cout << ans << endl;
}
