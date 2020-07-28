// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc08s5
#include <cstdio>
#include <cstring>
#define MAXN 31
int dp[MAXN][MAXN][MAXN][MAXN];
int solve(int a,int b,int c,int d){
	if(dp[a][b][c][d] != -1) return dp[a][b][c][d];
	int possiveis = 0,vencedoras = 0;
	if(a >= 2 && b >= 1 && d >= 2){
		possiveis++;
		if(solve(a-2,b-1,c,d-2) == 1){
			vencedoras++;
		}
	}
	if(a >= 1 && b >= 1 && c >= 1 && d >= 1){
		possiveis++;
		if(solve(a-1,b-1,c-1,d-1) == 1){
			vencedoras++;
		}
	}
	if(c >= 2 && d >= 1){
		possiveis++;
		if(solve(a,b,c-2,d-1) == 1){
			vencedoras++;
		}
	}
	if(b >= 3){
		possiveis++;
		if(solve(a,b-3,c,d) == 1){
			vencedoras++;
		}
	}
	if(a >= 1 && d >= 1){
		possiveis++;
		if(solve(a-1,b,c,d-1) == 1){
			vencedoras++;
		}
	}
	if(possiveis == vencedoras) return dp[a][b][c][d] = 0;
	return dp[a][b][c][d] = 1;
}
int main(){
	int TC;
	scanf("%d",&TC);
	memset(dp,-1,sizeof(dp));
	dp[2][1][0][2] = 1;
	dp[1][1][1][1] = 1;
	dp[0][0][2][1] = 1;
	dp[0][3][0][0] = 1;
	dp[1][0][0][1] = 1;
	while(TC--){
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		if(solve(a,b,c,d)) printf("Patrick\n");
		else printf("Roland\n");
	}
	return 0;
}