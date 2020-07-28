// Ivan Carvalho
// Solution to https://www.spoj.com/problems/WACHOVIA/
#include <cstdio>
#include <unordered_map>
#include <algorithm>
#define MAXN 201
using namespace std;
int valor[MAXN],peso[MAXN];
unordered_map<int,int> dp[MAXN];
int knapsack(int obj, int aguenta){
	if (obj <= 0 || aguenta == 0) return 0;
	if (dp[obj].count(aguenta)) return dp[obj][aguenta];
	int nao_coloca = knapsack(obj-1,aguenta);
	if (peso[obj] <= aguenta){
		int coloca = valor[obj] + knapsack(obj-1,aguenta-peso[obj]);
		return dp[obj][aguenta] = max(coloca,nao_coloca);
	} 
	return dp[obj][aguenta] = nao_coloca;
}
int main(){
	int casos;
	scanf("%d",&casos);
	while(casos--){
		int n,m;
		scanf("%d %d",&n,&m);
		for(int i=0;i<=m;i++) dp[i].clear();
		for(int i=1;i<=m;i++) scanf("%d %d",&peso[i],&valor[i]);
		printf("Hey stupid robber, you can get %d.\n",knapsack(m,n));
	}
	return 0;
}