// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco18p1
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 10;

int dp[MAXN][MAXN],matriz[2][MAXN],vetor[2][MAXN],N;
char entrada[MAXN];

int solve(int a,int b){
	if(dp[a][b] != -1) return dp[a][b];
	 if(a == 0 || b == 0) return 0;
	 if((vetor[0][a] > vetor[1][b] && matriz[0][a] == 1 && matriz[1][b] == 0) || (vetor[0][a] < vetor[1][b] && matriz[0][a] == 0 && matriz[1][b] == 1)){
	 	return dp[a][b] = max(solve(a-1,b-1) + vetor[0][a] + vetor[1][b], max(solve(a-1,b),solve(a,b-1))  );
	 }
	 else{
	 	return dp[a][b] = max(solve(a-1,b),solve(a,b-1));
	 }
}

int main(){
	memset(dp,-1,sizeof(dp));
	cin >> N;
	cin >> entrada;
	for(int i = 1;i<=N;i++){
		cin >> vetor[0][i];
		matriz[0][i] = (entrada[i-1] == 'W');
	}
	cin >> entrada;
	for(int i = 1;i<=N;i++){
		cin >> vetor[1][i];
		matriz[1][i] = (entrada[i-1] == 'W');
	}
	cout << solve(N,N) << endl;
	return 0;
}