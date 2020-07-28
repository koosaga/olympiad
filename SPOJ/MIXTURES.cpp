// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MIXTURES/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MODULO 100
#define LIMIT 1000000000
using namespace std;
int dp[MODULO+2][MODULO+2],somatorio[MODULO + 2],n;
int produtorio(int ini, int fim){
	return (somatorio[fim] - somatorio[ini-1]) % MODULO;
}
int func(int ini, int fim){
	if (dp[ini][fim] != -1) return dp[ini][fim];
	if (ini == fim) return dp[ini][fim] = 0;
	int ans = LIMIT;
	for(int k = ini; k < fim;k++){
		ans = min(ans,func(ini,k) + func(k+1,fim) + produtorio(ini,k) * produtorio(k+1,fim));
	}
	return dp[ini][fim] = ans;
}
int main(){
	while(scanf("%d",&n) != EOF){
		for(int i=1;i<=n;i++){
			int davez;
			scanf("%d",&davez);
			somatorio[i] = somatorio[i-1] + davez;
		}
		memset(dp,-1,sizeof(dp));
		printf("%d\n",func(1,n));
	}
}