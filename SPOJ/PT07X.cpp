// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PT07X/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int dp[MAXN][2],n;
vector<int> grafo[MAXN];
int solve(int v,int p,int estado){
	if(dp[v][estado] != -1) return dp[v][estado];
	int retorno = estado;
	for(int u : grafo[v]){
		if(u == p) continue;
		if(estado == 0){
			retorno += solve(u,v,1);
		}
		else{
			retorno += min(solve(u,v,1),solve(u,v,0));
		}
	}
	return dp[v][estado] = retorno;
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	for(int i = 1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	printf("%d\n",min(solve(1,-1,0),solve(1,-1,1)));
	return 0;
}