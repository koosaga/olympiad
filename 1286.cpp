// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1286
#include <bits/stdc++.h>
#define MAXN 1010
using namespace std;
long long int n,s,peso[MAXN],valor[MAXN];
map< pair<long long int, long long int> , long long int> tab;
long long int knapsack(long long int obj, long long int aguenta){
	pair< long long int, long long int> par = make_pair(obj,aguenta);
	if (tab.find(par)!=tab.end()) return tab[par];
	if (obj>n || !aguenta) return tab[par]=0;
	long long int nao_coloca = knapsack(obj+1,aguenta);
	if (peso[obj]<=aguenta){
		long long int coloca = valor[obj] + knapsack(obj+1,aguenta-peso[obj]);
		return tab[par]=max(coloca,nao_coloca);
	}
	return tab[par]=nao_coloca;
}
int main(){
	while(1){
		tab.clear();
		scanf("%lld",&n);
		if (n==0) break;
		scanf("%lld",&s);
		for (long long int i=1;i<=n;i++) scanf("%lld %lld",&valor[i],&peso[i]);
		printf("%lld min.\n",knapsack(1,s));
	}
	return 0;
}
