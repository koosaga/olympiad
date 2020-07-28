// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADACITY/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 501;
const int INF = 5*(1e8) + 1;
int matriz[MAXN][MAXN],amigo[MAXN],n,f,m,t;
vector<int> grafo[MAXN],match,vis;
int augmenting_path(int l){
	if(vis[l]) return 0;
	vis[l] = 1;
	for(int i=0;i<grafo[l].size();i++){
		int r = grafo[l][i];
		if(match[r] == -1 || augmenting_path(match[r])){
			match[r] = l;
			return 1;
		}
	}
	return 0;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d %d %d %d",&n,&m,&f,&t);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				matriz[i][j] = INF;
			}
			matriz[i][i] = 0;
		}
		for(int i=1;i<=f;i++){
			grafo[i].clear();
			scanf("%d",&amigo[i]);
		}
		for(int i=1;i<=m;i++){
			int u,v,peso;
			scanf("%d %d %d",&u,&v,&peso);
			matriz[u][v] = min(matriz[u][v],peso);
			matriz[v][u] = min(matriz[v][u],peso);
		}
		for(int k=1;k<=n;k++){
			for(int j=1;j<=n;j++){
				for(int i=1;i<=n;i++){
					matriz[i][j] = min(matriz[i][j],matriz[i][k] + matriz[k][j]);
				}
			}
		}
		for(int i=1;i<=f;i++){
			for(int j=1;j<=n;j++){
				if(matriz[amigo[i]][j] <= t){
					grafo[i].push_back(j);
				}
			}
		}
		int resp = 0;
		match.assign(n+2,-1);
		for(int i=1;i<=f;i++){
			vis.assign(f+1,0);
			resp += augmenting_path(i);
		}
		printf("%d\n",resp);
	}
	return 0;
}