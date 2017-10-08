#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m;
vector<int> graph[50005];
vector<int> bcc[50005];
vector<int> by_col[50005];

bool vis[50005];
int low[50005], dfn[50005], piv;

void dfs(int x, int p){
	low[x] = dfn[x] = ++piv;
	vis[x] = 1;
	for(auto &i : graph[x]){
		if(i == p) continue;
		if(vis[i]) low[x] = min(low[x], dfn[i]);
		else{
			dfs(i, x);
			low[x] = min(low[x], low[i]);
		}
	}
}

int cols;

void color(int x, int p, int c){
	vis[x] = 1;
	if(c) bcc[x].push_back(c), by_col[c].push_back(x);
	for(auto &i : graph[x]){
		if(vis[i]) continue;
		if(low[i] >= dfn[x]){
			bcc[x].push_back(++cols);
			by_col[cols].push_back(x);
			color(i, x, cols);
		}
		else color(i, x, c);
	}
}

int tc;

bool solve(){
	scanf("%d",&m);
	if(m == 0) return 0;
	n = piv = cols = 0;
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		n = max(s, n);
		n = max(e, n);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	dfs(1, 0);
	memset(vis, 0, sizeof(vis));
	color(1, 0, 0);
	long long ret = 1;	
	int cnt = 0;
	printf("Case %d: ",++tc);
	for(int i=1; i<=cols; i++){
		int cuts = 0;
		for(auto &j : by_col[i]){
			if(bcc[j].size() > 1) cuts++;
		}
		if(cuts == 0){
			printf("2 %lld\n", 1ll * n * (n-1) / 2);
			return 1;
		}
		else if(cuts == 1){
			cnt++;
			ret *= by_col[i].size() - 1;
		}
	}
	printf("%d %lld\n",cnt, ret);
	return 1;
}

int main(){
	while(solve()){
		for(int i=1; i<=n; i++) graph[i].clear();
		for(int i=1; i<=n; i++) bcc[i].clear();
		for(int i=1; i<=cols; i++) by_col[i].clear();
		memset(vis, 0, sizeof(vis));
		memset(low, 0, sizeof(low));
		memset(dfn, 0, sizeof(dfn));
	}
}
