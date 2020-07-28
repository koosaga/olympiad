// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c3p4
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5*1e5 + 10;
const int MAXK = 653;

int dp[MAXK][MAXK],matriz[MAXK][MAXK],A[MAXN],B[MAXN],N;

int calcula(int x1,int y1,int x2,int y2){
	if(x1 > x2 || y1 > y2) return 0;
	return dp[x2][y2] - dp[x1-1][y2] - dp[x2][y1 - 1] + dp[x1-1][y1-1];
}

int main(){
	
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		scanf("%d %d",&A[i],&B[i]);
		A[i]++;B[i]++;
		dp[A[i]][B[i]]++;
		matriz[A[i]][B[i]]++;
	}

	for(int i = 1;i<MAXK;i++){
		for(int j = 1;j<MAXK;j++){
			dp[i][j] += dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
		}
	}

	for(int i = 1;i<=N;i++){
		int x = A[i],y = B[i];
		int melhores = calcula(x+1,y+1,MAXK-1,MAXK-1);
		int piores = calcula(1,1,x-1,y-1);
		if(A[i] == 651) piores += matriz[1][B[i]];
		if(B[i] == 651) piores += matriz[A[i]][1];
		printf("%d %d\n",melhores+1,N - piores);
	}

	return 0;
}