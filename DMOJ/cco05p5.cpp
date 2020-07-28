// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco05p5
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20100;


int dp[MAXN][2],P[MAXN][2],N;

int dist(int A,int B){
	return max(A-B,B-A);
}

int solve(int atual,int lado){
	if(atual == N + 2) return 0;
	if(dp[atual][lado] != -1) return dp[atual][lado];
	int pos = P[atual-1][lado];
	int v1 = solve(atual+1,1) + dist(pos,P[atual][0]) + dist(P[atual][0],P[atual][1]);
	int v2 = solve(atual+1,0) + dist(pos,P[atual][1]) + dist(P[atual][1],P[atual][0]);
	return dp[atual][lado] = min(v1,v2);
}

int main(){
	while(scanf("%d",&N) != EOF){
		if(N == 0) break;
		memset(dp,-1,sizeof(dp));
		for(int i = 1;i<=N;i++) scanf("%d %d",&P[i][0],&P[i][1]);
		P[0][0] = P[0][1] = 1;
		P[N+1][0] = P[N+1][1] = N;
		printf("%d\n",solve(1,0) + N-1);
	}
	return 0;
}