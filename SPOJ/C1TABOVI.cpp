// Ivan Carvalho
// Solution to https://www.spoj.com/problems/C1TABOVI/
#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 1010;
const int MAXP = 82;
const int INF = 1e8 + 10;
 
int dp[MAXN][MAXP][MAXP],vetor[MAXN],alvo[MAXN],N;
 
int solve(int pos,int a,int b){
	if(pos == N + 1) return 0;
	if(a < 0 || b < 0 || a >= MAXP || b >= MAXP) return INF;
	if(dp[pos][a][b] != -1) return dp[pos][a][b];
	int qtd = vetor[pos] + a - b;
	if(qtd == alvo[pos]) return dp[pos][a][b] = solve(pos+1,a,b);
	else if(qtd < alvo[pos]) return dp[pos][a][b] = min( solve(pos,a+1,b) + 1, solve(pos,a,b-1) );
	else return dp[pos][a][b] = min( solve(pos,a,b+1) + 1, solve(pos,a-1,b) );
}
 
int main(){
	scanf("%d",&N);
	memset(dp,-1,sizeof(dp));
	for(int i = 1;i<=N;i++) scanf("%d",&vetor[i]);
	for(int i = 1;i<=N;i++) scanf("%d",&alvo[i]);
	printf("%d\n",solve(1,0,0));
	return 0;
} 
