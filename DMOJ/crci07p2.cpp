// Ivan Carvalho
// Solution to https://dmoj.ca/problem/crci07p2
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1001;
const int INF = 1e8;
int dp[MAXN][MAXN];
int vetor[MAXN],n;
int solve(int pos,int jump){
	if(pos == n) return vetor[pos];
	if(pos > n || pos < 1) return INF;
	if(dp[pos][jump] != -1) return dp[pos][jump];
	int resp = vetor[pos];
	int v1 = INF,v2 = INF;
	if(jump != 0) v1 = solve(pos - jump,jump);
	v2 = solve(pos+jump+1,jump+1);
	return dp[pos][jump] = min(v1,v2) + resp;
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++) scanf("%d",&vetor[i]);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",solve(2,1));
	return 0;
}