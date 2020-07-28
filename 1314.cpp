// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1314
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 10001
using namespace std;
vector<int> grafo[MAXN];
int pai[MAXN],dfs_low[MAXN],dfs_num[MAXN],dfs_parent[MAXN],pontosdearticulacao[MAXN],dfsNumberCounter,dfsRoot,dfsRootChildren,n,m,q;
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x=find(x);y=find(y);
	if(x==y) return;
	if(x>y) swap(x,y);
	pai[y] = x;
}
void dfs(int u){
	dfs_low[u] = dfs_num[u] = ++dfsNumberCounter;
	for(int i=0;i<grafo[u].size();i++){
		int v = grafo[u][i];
		if(dfs_num[v] == 0){
			dfs_parent[v] = u;
			if(u == dfsRoot) dfsRootChildren++;
			dfs(v);
			if(dfs_low[v] >= dfs_num[u]){
				pontosdearticulacao[u] = 1;
			}
			if(dfs_low[v] > dfs_num[u]){
				//printf("%d %d is bridge\n",u,v);
				join(u,v);
			}
			dfs_low[u] = min(dfs_low[v],dfs_low[u]);
		}
		else if(v != dfs_parent[u]){
			dfs_low[u] = min(dfs_low[v],dfs_low[u]);
		}
	}
}
int main(){
	while(scanf("%d %d %d",&n,&m,&q) && (n||m||q)){
		for(int i=1;i<=n;i++){
			pai[i] = i;
			dfs_low[i] = dfs_num[i] = dfs_parent[i] = pontosdearticulacao[i] = 0;
			grafo[i].clear();
		}
		dfsNumberCounter = 0;
		while(m--){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		for(int i=1;i<=n;i++){
			if(dfs_num[i] == 0){
				dfsRoot = i;
				dfsRootChildren = 0;
				dfs(i);
				pontosdearticulacao[i] = (dfsRootChildren > 1);
			}
		}
		while(q--){
			int u,v;
			scanf("%d %d",&u,&v);
			printf("%c\n",find(u) == find(v) ? 'Y' : 'N');
		}
		printf("-\n");
	}
	return 0;
}
