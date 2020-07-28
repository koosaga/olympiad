// Ivan Carvalho
// Solution to https://www.spoj.com/problems/NTICKETS/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
const int MAXL = 18;
int n,q,ancestral[MAXN][MAXL],maior[MAXN][MAXL],nivel[MAXN];
vector<ii> grafo[MAXN];
void dfs(int v,int p){
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first, peso = grafo[v][i].second;
		if(u == p) continue;
		ancestral[u][0] = v;
		maior[u][0] = peso;
		nivel[u] = nivel[v] + 1;
		dfs(u,v);
	}
}
int LCA(int u,int v){
	int resp = 0;
	if(nivel[u] < nivel[v]) swap(u,v);
	for(int i = MAXL - 1;i>=0;i--){
		int prox = ancestral[u][i];
		if(prox != -1 && nivel[prox] >= nivel[v]){
			resp = max(resp,maior[u][i]);
			u = prox;
		}
	}
	if(u == v) return resp;
	for(int i = MAXL - 1;i>=0;i--){
		int proxu = ancestral[u][i],proxv = ancestral[v][i];
		if(proxu != -1 && proxu != proxv){
			resp = max(resp,maior[u][i]);
			resp = max(resp,maior[v][i]);
			u = proxu;
			v = proxv;
		}
	}
	return max(max(maior[u][0],maior[v][0]),resp);
}
int main(){
	while(scanf("%d",&n) && n){
		for(int i = 1;i<=n;i++){
			grafo[i].clear();
			nivel[i] = 0;
			memset(ancestral[i],-1,sizeof(ancestral[i]));
			memset(maior[i],0,sizeof(maior[i]));
		}
		for(int i = 1;i<n;i++){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			grafo[u].push_back(ii(v,peso));
			grafo[v].push_back(ii(u,peso));
		}
		dfs(1,-1);
		for(int j = 1;j<MAXL;j++){
			for(int i = 1;i<=n;i++){
				int prox = ancestral[i][j-1];
				if(prox != -1){
					int peso = maior[prox][j-1];
					ancestral[i][j] = ancestral[prox][j-1];
					maior[i][j] = max(maior[i][j],peso);
				}
				maior[i][j] = max(maior[i][j],maior[i][j-1]);
			}
		}
		scanf("%d",&q);
		while(q--){
			int u,v;
			scanf("%d %d",&u,&v);
			printf("%d\n",LCA(u,v));
		}
		printf("\n");
	}
	return 0;
}