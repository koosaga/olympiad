// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1372
#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;
int dp[MAXN],tab[MAXN],best[MAXN],vetor[MAXN],n,m;
int solve(int pos){
	if(pos >= n) return 0;
	if(tab[pos] != -1) return tab[pos];
	return tab[pos] = max(vetor[pos] + solve(pos+2),solve(pos+1));
}
int func(int line){
	if(line >= m) return 0;
	if(dp[line] != -1) return dp[line];
	return dp[line] = max(best[line] + func(line+2),func(line+1));
}
int main(){
	while(scanf("%d %d",&m,&n) && (n || m)){
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				scanf("%d",&vetor[j]);
				tab[j] = -1;
			}
			dp[i] = -1;
			best[i] = solve(0);
		}
		printf("%d\n",func(0));
	}
	return 0;
}
