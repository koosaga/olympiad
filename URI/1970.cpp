// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1970
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 101
#define MAXL 51
using namespace std;
int dp[MAXN][MAXL][MAXL][MAXL],peso[MAXN],fitas[4];
int func(int n, int aguenta1, int aguenta2, int aguenta3){
	if (aguenta3 < aguenta1) swap(aguenta3,aguenta1);
	if (aguenta2 < aguenta1) swap(aguenta2,aguenta1);
	if (aguenta3 < aguenta2) swap(aguenta2,aguenta3);
	if (n <= 0 || (aguenta1 <= 0 && aguenta2 <= 0 && aguenta3 <= 0)) return 0;
	if (dp[n][aguenta1][aguenta2][aguenta3] != -1) return dp[n][aguenta1][aguenta2][aguenta3];
	int nao_coloca = func(n-1,aguenta1,aguenta2,aguenta3),coloca1 = 0, coloca2 = 0, coloca3 = 0;
	if (peso[n] <= aguenta1){
		coloca1 = peso[n] + func(n-1,aguenta1-peso[n],aguenta2,aguenta3);
	}
	if (peso[n] <= aguenta2){
		coloca2 = peso[n] + func(n-1,aguenta1,aguenta2-peso[n],aguenta3);
	}
	if (peso[n] <= aguenta3){
		coloca3 = peso[n] + func(n-1,aguenta1,aguenta2,aguenta3-peso[n]);
	}
	return dp[n][aguenta1][aguenta2][aguenta3] = max(max(max(coloca1,coloca2),coloca3),nao_coloca);
}
int main(){
	memset(dp,-1,sizeof(dp));
	int n,k;
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&peso[i]);
	for(int i=1;i<=k;i++) scanf("%d",&fitas[i]);
	printf("%d\n",func(n,fitas[1],fitas[2],fitas[3]));
	return 0;
}
