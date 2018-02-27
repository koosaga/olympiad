#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n, m;
int dfn[MAXN], low[MAXN], piv, c;
vector<int> gph[MAXN], bcc[MAXN], cmp[MAXN];
lint ans[MAXN];

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(!dfn[i]){
			dfs(i, x);
			low[x] = min(low[x], low[i]);
		}
		else low[x] = min(low[x], dfn[i]);
	}
}

void color(int x, int p){
	if(p){
		bcc[p].push_back(x);
		cmp[x].push_back(p);
	}
	for(auto &i : gph[x]){
		if(cmp[i].size()) continue;
		if(low[i] >= dfn[x]){
			bcc[++c].push_back(x);
			cmp[x].push_back(c);
			color(i, c);
		}
		else color(i, p);
	}
}

int dfs2(int x){
	int tot = 0;
	for(int i=1; i<bcc[x].size(); i++){
		int v = bcc[x][i];
		int vtxsub = 1;
		for(auto &j : cmp[v]){
			if(j == x) continue;
			int dodal = dfs2(j);
			ans[v] += 1ll * dodal * dodal;
			vtxsub += dodal;
		}
		ans[v] += 1ll * (n - vtxsub) * (n - vtxsub);
		tot += vtxsub;
	}
	return tot;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	color(1, 0);
	int vtxsub = 0;
	for(auto &i : cmp[1]){
		int dodal = dfs2(i);
		ans[1] += 1ll * dodal * dodal;
		vtxsub += dodal;
	}
	ans[1] += 1ll * (n - vtxsub - 1) * (n - vtxsub - 1);

	for(int i=1; i<=n; i++){
		printf("%lld\n", 1ll * n * n - 1 - ans[i]);
	}
}


