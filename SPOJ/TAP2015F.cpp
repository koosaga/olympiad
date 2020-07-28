// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2015F/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int MAXN = 5*(1e4 + 1);
const int MAXE = 51;
vector<int> grafo[MAXN];
int n,e,cordefinida[MAXN];
ll matriz[MAXE][MAXE],dp[MAXN][MAXE];
ll solve(int vertice,int time,int pai){
	if(dp[vertice][time] != -1) return dp[vertice][time];
	ll retorna  = 0;
	for(int i=0;i<grafo[vertice].size();i++){
		int u = grafo[vertice][i];
		if(u == pai) continue;
		if(cordefinida[u] != 0){
			retorna += matriz[time][cordefinida[u]] + solve(u,cordefinida[u],vertice);
		}
		else{
			ll minimo = INF;
			for(int j=1;j<=e;j++){
				minimo = min(minimo, matriz[time][j] + solve(u,j,vertice) );
			}
			retorna += minimo;
		}
	}
	return dp[vertice][time] = retorna;
}
int main(){
	while(scanf("%d %d",&n,&e) != EOF){
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			cordefinida[i] = 0;
			for(int j=1;j<=e;j++){
				dp[i][j] = -1;
			}
		}
		for(int i=1;i<=e;i++){
			for(int j=1;j<=e;j++){
				scanf("%lld",&matriz[i][j]);
			}
		}
		for(int i=1;i<=e;i++){
			int qtd;
			scanf("%d",&qtd);
			while(qtd--){
				int u;
				scanf("%d",&u);
				cordefinida[u] = i;
			}
		}
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d %d",&u,&v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		ll exibir = INF;
		if(cordefinida[1]){
			exibir = solve(1,cordefinida[1],-1);
		}
		else{
			for(int j=1;j<=e;j++){
				exibir = min(exibir, solve(1,j,-1) );
			}
		}
		printf("%lld\n",exibir);
	}
	return 0;
}