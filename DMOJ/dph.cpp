// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dph
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
const int MOD = 1e9 + 7;

char entrada[MAXN][MAXN];
int dp[MAXN][MAXN],vis[MAXN][MAXN];
int N,M;

int solve(int x,int y){

	if(x >= N || y >= M) return 0;
	if(entrada[x][y] == '#') return 0;

	if(vis[x][y]) return dp[x][y];
	if(x == N - 1 && y == M - 1) return dp[x][y] = 1;

	vis[x][y] = 1;
	return dp[x][y] = (solve(x+1,y) + solve(x,y+1)) % MOD;

}

int main(){

	scanf("%d %d",&N,&M);
	for(int i = 0;i<N;i++){
		scanf("%s",entrada[i]);
	}

	printf("%d\n",solve(0,0));

	return 0;

}