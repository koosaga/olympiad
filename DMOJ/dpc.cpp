// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpc
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

int vis[MAXN][3],dp[MAXN][3],N,A[3][MAXN];

int solve(int pos,int last){

	if(pos == N + 1) return 0;

	if(vis[pos][last]) return dp[pos][last];
	vis[pos][last] = 1;

	int best = 0;

	for(int i = 0;i<3;i++){
		if(i != last) best = max(best, A[i][pos] + solve(pos+1,i) );
	}

	return dp[pos][last] = best;

}

int main(){

	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		scanf("%d %d %d",&A[0][i],&A[1][i],&A[2][i]);
	}

	printf("%d\n", max(solve(1,0), max(solve(1,1),solve(1,2)) ) );

	return 0;

}