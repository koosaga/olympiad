// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MUSKET/
#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 210;
 
int dp[MAXN][MAXN][MAXN],N,matriz[MAXN][MAXN],possivel[MAXN];
char entrada[MAXN];
 
inline int converte(int x){
	if(x > N) return x - N;
	return x;
}
 
int solve(int k,int i,int j){
	if(dp[k][i][j] != -1) return dp[k][i][j];
	if(k < i && k > j) return dp[k][i][j] = 0;
	if(k == i){
		if(i == j) return dp[k][i][j] = 1;
		for(int l = i+1;l<=j;l++){
			if(matriz[converte(k)][converte(l)]*solve(l,i+1,j)) return dp[k][i][j] = 1;
		}
		return dp[k][i][j] = 0;
	}
	else if(k == j){
		for(int l = j - 1;l>=i;l--){
			if(matriz[converte(k)][converte(l)]*solve(l,i,j-1)) return dp[k][i][j] = 1;
		}
		return dp[k][i][j] = 0;
	}
	else{
		return dp[k][i][j] = solve(k,i,k) && solve(k,k,j);
	}
}
 
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&N);
		memset(dp,-1,sizeof(dp));
		memset(matriz,0,sizeof(matriz));
		memset(possivel,0,sizeof(possivel));
		for(int i = 1;i<=N;i++){
			scanf("%s",entrada);
			for(int j = 1;j<=N;j++){
				matriz[i][j] = (entrada[j-1] == '1');
			}
		}
		for(int ini = 1,fim = N;ini<=N;ini++,fim++){
			for(int i = 1;i<=2*N;i++){
				possivel[converte(i)] |= solve(i,ini,fim);
			}
		}
		int ans = 0;
		for(int i = 1;i<=N;i++) ans += possivel[i];
		printf("%d\n",ans);
		for(int i = 1;i<=N;i++){
			if(possivel[i]) printf("%d\n",i);
		}
	}
	return 0;
} 
