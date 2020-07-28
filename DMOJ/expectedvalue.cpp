// Ivan Carvalho
// Solution to https://dmoj.ca/problem/expectedvalue
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e3 + 10;
const int MOD = 998244353;
const ll INVMOD[11] = {0,
 	1LL,
 	499122177LL,
 	332748118LL,
 	748683265LL,
 	598946612LL,
 	166374059LL,
 	855638017LL,
 	873463809LL,
 	443664157LL,
 	299473306LL
};

ll dp[MAXN][MAXN][2],matriz[MAXN][MAXN],prob[2];
int N,A,B;

ll solve(int x,int y,int o){
	if(dp[x][y][o] != -1) return dp[x][y][o];
	if(x == N && y == N) return dp[x][y][o] = matriz[x][y];
	int nx = x + (o == 1 ? 1 : 0);
	int ny = y + (o == 1 ? 0 : 1);
	if(nx > N || ny > N) return dp[x][y][o] = solve(x,y,o ^ 1);
	ll ans = prob[0]*solve(nx,ny,o) + prob[1]*solve(nx,ny,o ^ 1);
	return dp[x][y][o] = (matriz[x][y] + ans) % MOD; 
}

int main(){

	scanf("%d %d",&A,&B);
	prob[0] = ((B-A)*INVMOD[B]) % MOD;
	prob[1] = (A*INVMOD[B]) % MOD;

	memset(dp,-1,sizeof(dp));
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		for(int j = 1;j<=N;j++) scanf("%lld",&matriz[i][j]);
	}

	ll ans = prob[0]*solve(1,1,1) + prob[1]*solve(1,1,0);
	printf("%lld\n",ans % MOD);

	return 0;

}
