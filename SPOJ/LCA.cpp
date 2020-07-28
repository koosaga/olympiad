// Ivan Carvalho
// Solution to https://www.spoj.com/problems/LCA/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1010;
vector<int> grafo[MAXN];
vector<ii> queries[MAXN];
int pai[MAXN],peso[MAXN],resposta[MAXN],cor[MAXN],ancestral[MAXN],n,m;
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(peso[x] < peso[y]) swap(x,y);
	peso[x] += peso[y];
	pai[y] = x;
}
void dfs(int v,int p){
	pai[v] = v;
	ancestral[v] = v;
	for(int u : grafo[v]){
		if(u == p) continue;
		dfs(u,v);
		join(u,v);
		ancestral[find(v)] = v;
	}
	cor[v] = 1;
	for(int i = 0;i<queries[v].size();i++){
		int u = queries[v][i].first, idx = queries[v][i].second;
		if(cor[u] == 1) resposta[idx] = ancestral[find(u)];
	}
}
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc = 1;tc<=TC;tc++){
		scanf("%d",&n);
		for(int i = 1;i<=n;i++){
			pai[i] = i;
			peso[i] = 0;
			cor[i] = 0;
			ancestral[i] = i;
			grafo[i].clear();
			queries[i].clear();
		}
		for(int i = 1;i<=n;i++){
			int qtd;
			scanf("%d",&qtd);
			while(qtd--){
				int j;
				scanf("%d",&j);
				grafo[i].push_back(j);
				grafo[j].push_back(i);
			}
		}
		scanf("%d",&m);
		for(int i = 1;i<=m;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			queries[u].push_back(ii(v,i));
			queries[v].push_back(ii(u,i));
		}
		dfs(1,-1);
		printf("Case %d:\n",tc);
		for(int i = 1;i<=m;i++){
			printf("%d\n",resposta[i]);
		}
	}
	return 0;
}