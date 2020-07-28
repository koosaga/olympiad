// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c6p2
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int dp[MAXN][MAXN][MAXN][MAXN],tipo[MAXN][3],N,M;
set<char> entrada[MAXN];

int solve(int pos,int a,int b,int c){
	if(a == 0 && b == 0 && c == 0) return 1;
	if(pos == M + 1) return 0;
	if(dp[pos][a][b][c] != -1) return dp[pos][a][b][c];
	int possivel = 0;
	if(entrada[pos].count('O')) possivel |= solve(pos+1,max(a-1,0),b,c);
	if(entrada[pos].count('V')) possivel |= solve(pos+1,a,max(b-1,0),c);
	if(entrada[pos].count('N')) possivel |= solve(pos+1,a,b,max(c-1,0));
	return dp[pos][a][b][c] = possivel;
}

int main(){
	
	memset(dp,-1,sizeof(dp));
	scanf("%d",&N);
	for(int i = 1;i<=N;i++) scanf("%d%*c%d%*c%d",&tipo[i][0],&tipo[i][1],&tipo[i][2]);
	
	scanf("%d",&M);
	for(int i = 1;i<=M;i++){
		string s;
		cin >> s;
		for(char c : s) entrada[i].insert(c);
	}
	
	for(int i = 1;i<=N;i++){
		if(solve(1,tipo[i][0],tipo[i][1],tipo[i][2])) printf("DA\n");
		else printf("NE\n");
	}

	return 0;
}