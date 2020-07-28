// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg18s6
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
vector<int> grafo[MAXN];
int sz[MAXN],low[MAXN],num[MAXN],parent[MAXN],dfsPtr,rootChildren,articulation[MAXN],mx[MAXN],maior,vertice,N,M;
void dfs(int v){
	sz[v] = 1;
	num[v] = low[v] = ++dfsPtr;
	for(int u : grafo[v]){
		if(parent[u] == 0){
			if(v == 1) rootChildren++;
			parent[u] = v;
			dfs(u);
			sz[v] += sz[u];
			low[v] = min(low[v],low[u]);
		}
		else if(parent[v] != u){
			low[v] = min(low[v],num[u]);
		}
	}
	int best = 0;
	if(v == 1){
		if(rootChildren == 1) return;
		articulation[v] = 1;
		for(int u : grafo[v]) best = max(best,sz[u]);
		mx[v] = best;
	}
	else{
		for(int u : grafo[v]){
			if(parent[u] == v && low[u] >= num[v]) articulation[v] = 1;
		}
		if(!articulation[v]) return;
		best = N - sz[v];
		for(int u : grafo[v]){
			if(parent[u] == v && low[u] < num[v]) best += sz[u];
		}
		for(int u : grafo[v]){
			if(parent[u] == v && low[u] >= num[v]) best = max(best,sz[u]);
		}
		mx[v] = best;
	}
}
int main(){
	scanf("%d %d",&N,&M);
	for(int i = 1;i<=M;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	parent[1] = 1;
	dfs(1);
	maior = 2*N;
	for(int i = 1;i<=N;i++){
		if(!articulation[i]) continue;
		if(mx[i] <= maior){
			maior = mx[i];
			vertice = i;
		}
	}
	if(maior > N) printf("-1 -1\n");
	else printf("%d %d\n",vertice,maior);
	return 0;
}
