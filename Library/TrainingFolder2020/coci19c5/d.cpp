#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int mod = 1e9 + 7;
const int MAXN = 200005;

struct edg{
	int pos, c[2];
};

int n;
vector<edg> gph[MAXN];

int par[18][MAXN], pae[MAXN][2], dep[MAXN], dx[MAXN];

void dfs2(int x, int p){
	for(auto &i : gph[x]){
		if(i.pos != p){
			dfs2(i.pos, x);
			dx[x] += dx[i.pos];
		}
	}
}

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i.pos != p){
			dep[i.pos] = dep[x] + 1;
			par[0][i.pos] = x;
			pae[i.pos][0] = i.c[0];
			pae[i.pos][1] = i.c[1];
			dfs(i.pos, x);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int u, v, x, y; scanf("%d %d %d %d",&u,&v,&x,&y);
		edg e; e.pos = v, e.c[0] = x; e.c[1] = y;
		gph[u].push_back(e);
		e.pos = u; 
		gph[v].push_back(e);
	}
	dfs(1, 0);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	auto lca = [&](int x, int y){
		if(dep[x] < dep[y]) swap(x, y);
		int dx = dep[x] - dep[y];
		for(int i=0; i<18; i++){
			if((dx >> i) & 1) x = par[i][x];
		}
		for(int i=17; i>=0; i--){
			if(par[i][x] != par[i][y]){
				x = par[i][x];
				y = par[i][y];
			}
		}
		if(x != y) return par[0][x];
		return x;
	};
	for(int i=2; i<=n; i++){
		int l = lca(i - 1, i);
		dx[i]++; dx[i-1]++; dx[l] -= 2;
	}
	dfs2(1, 0);
	lint ret = 0;
	for(int i=2; i<=n; i++){
		ret += min(1ll * pae[i][1], 1ll * pae[i][0] * dx[i]);
	}
	cout << ret << endl;
}
