// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SUBMERGE/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 10;
vector<int> grafo[MAXN];
int dfsNum[MAXN],dfsLow[MAXN],dfsParent[MAXN],dfsRoot,articulation_point[MAXN],pontes,dfsCount,RootChildren;
void dfs(int x){
	dfsNum[x] = ++dfsCount;
	dfsLow[x] = dfsNum[x];
	for(int i=0;i<grafo[x].size();i++){
		int v = grafo[x][i];
		if(dfsNum[v] == 0){
			dfsParent[v] = x;
			if(x == dfsRoot) RootChildren++;
			dfs(v);
			if(dfsNum[x] <= dfsLow[v]) articulation_point[x] = 1;
			if(dfsNum[x] < dfsLow[v]) pontes++;
			dfsLow[x] = min(dfsLow[x],dfsLow[v]);
		}
		else if(v != dfsParent[x]){
			dfsLow[x] = min(dfsLow[x],dfsNum[v]);
		}
	}
}
int main(){
	int n,m;
	while(scanf("%d %d",&n,&m) && (n||m)){
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			dfsNum[i] = dfsLow[i] = dfsParent[i] = articulation_point[i] = 0;
		}
		dfsCount = 0;
		RootChildren = 0;
		pontes = 0;
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		dfsRoot = 1;
		dfs(1);
		articulation_point[1] = (RootChildren>1);
		int resp = 0;
		for(int i=1;i<=n;i++) resp += articulation_point[i];
		printf("%d\n",resp);
	}
	return 0;
}