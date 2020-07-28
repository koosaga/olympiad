// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c5p5
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 205;

int dp[MAXN][MAXN],N;
int vetor[MAXN];

int solve(int i,int j){
	if(dp[i][j] != -1) return dp[i][j];
	if(i == j) return dp[i][j] = vetor[i];
	return dp[i][j] = max(vetor[i] - solve(i+1,j), vetor[j] - solve(i,j-1) );
}

int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		scanf("%d",&vetor[i]);
		vetor[i] %= 2;
		vetor[i+N] = vetor[i];
	}
	int total = 0;
	for(int i = 1;i<=N;i++){
		int resultado = vetor[i] - solve(i+1,i + N - 1);
		if(resultado > 0) total++;
	}
	printf("%d\n",total);
	return 0;
}