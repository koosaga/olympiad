#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int n, a[MAXN][3], col[MAXN];
vector<int> gph[MAXN];
int dfn[MAXN], low[MAXN], piv;

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(!dfn[i]){
			dfs(i, x);
			low[x] = min(low[x], low[i]);
		}
		else{
			low[x] = min(low[x], dfn[i]);
		}
	}
}

vector<int> cmp[MAXN];

void color(int x, int p){
	cmp[where[x]].push_back(x);
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(!where[i]){
			if(low[i] > dfn[x]) where[i] = ++piv;
			else where[i] = where[x];
			color(i, p);
		}
}

void init(){
	dfs(1, 0);
}

void update(int x){
	init();
}

int main(){
	int m, q;
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1; i<=n; i++){
		for(int j=0; j<3; j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1; i<=m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	init();
	while(q--){
		int x, v, w; scanf("%d %d %d",&x,&v,&w);
		a[x][v-1] = w;
		update(v);
		printf("%d\n", dap);
	}
}

