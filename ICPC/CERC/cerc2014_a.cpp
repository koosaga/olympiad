#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
 
vector<int> graph[1005];
vector<pi> paths[1005];
 
int n, m;
int par[1005];
int dfn[1005], rev[1005], size[1005], piv;
int dep[1005];
 
void dfs(int x, int p){
	dfn[x] = ++piv;
	rev[dfn[x]] = x;
	size[x] = 1;
	par[x] = p;
	for(auto &i : graph[x]){
		if(i == p) continue;
		dep[i] = dep[x] + 1;
		dfs(i, x);
		size[x] += size[i];
	}
}
 
int L[1005][1005];
int submask[1005][1005];
 
bool in_subtree(int root, int pos){
	return dfn[root] <= dfn[pos] && dfn[pos] <= dfn[root] + size[root] - 1;
}
 
void input(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	dfs(1,0);
	for(int i=2; i<=n; i++){
		graph[i].erase(find(graph[i].begin(), graph[i].end(), par[i]));
	}
	for(int i=1; i<=n; i++){
		int s = rev[i];
		L[s][s] = s;
		for(int j=i+1; j<=n; j++){
			int e = rev[j];
			if(dep[s] < dep[e]) L[s][e] = L[s][par[e]];
			else L[s][e] = L[par[s]][e];
			L[e][s] = L[s][e];
		}
	}
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		paths[L[s][e]].push_back(pi(s,e));
	}
	for(int i=1; i<=n; i++){
		for(int j=i; j<=n; j++){
			int s = rev[i], e = rev[j];
			for(int k=0; k<graph[s].size(); k++){
				if(in_subtree(graph[s][k],e)){
					submask[s][e] = (1<<k);
					break;
				}
			}
		}
	}
}
 
int dp[1005][1<<10];
int dp2[1005];
int tabl[1<<10];

void solve(){
	for(int i=n; i; i--){
		int pos = rev[i];
		memset(dp2,0,sizeof(dp2));
		memset(tabl,0,sizeof(tabl));
		for(int j=i+1; j<=n; j++){
			int x = rev[j];
			dp2[x] = dp2[par[x]] + dp[par[x]][submask[par[x]][x]];
		}
		for(auto &j : paths[pos]){
			int ret = 1;
			if(j.first != pos){
				ret += dp[j.first][0] + dp2[j.first];
			}
			if(j.second != pos){
				ret += dp[j.second][0] + dp2[j.second];
			}
			int mask = (submask[pos][j.first] | submask[pos][j.second]);
			tabl[mask] = max(tabl[mask], ret);
		}
		for(int j=(1<<graph[pos].size()) - 1; j>=0; j--){
			for(int k=0; k<graph[pos].size(); k++){
				if(((j >> k) & 1) == 0){
					dp[pos][j] = max(dp[pos][j], dp[pos][j|(1<<k)] + dp[graph[pos][k]][0]);
					dp[pos][j] = max(dp[pos][j], dp[pos][j|(1<<k)] + tabl[1<<k]);
					for(int l=k+1; l<graph[pos].size(); l++){
						if(((j >> l) & 1) == 0){
							dp[pos][j] = max(dp[pos][j], dp[pos][j|(1<<k)|(1<<l)] + tabl[(1<<k)|(1<<l)]);
						}
					}
				}
			}
		}
	}
	printf("%d\n",dp[1][0]);
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		input();
		solve();
		for(int i=0; i<=n; i++){
			graph[i].clear();
			paths[i].clear();
		}
		memset(dp,0,sizeof(dp));
		memset(submask,0,sizeof(submask));
		memset(L,0,sizeof(L));
		piv = 0;
	}
}