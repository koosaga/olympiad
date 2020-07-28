// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco15p2
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 18;
const int MAXM = (1<<MAXN);
int matriz[MAXN][MAXN];
int dp[MAXN][MAXM];
int n,m;
int solve(int pos,int bitmask){
	if(dp[pos][bitmask] != -1) return dp[pos][bitmask];
	if(pos == n-1){
		return dp[pos][bitmask] = 0;
	}
	int ans = -1e8;
	for(int nxt=0;nxt<n;nxt++){
		if(matriz[pos][nxt] > 0 && !(bitmask & (1<<nxt))){
			ans = max(matriz[pos][nxt] + solve(nxt,bitmask | (1<<nxt)),ans);
		}
	}
	return dp[pos][bitmask] = ans;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		matriz[u][v] = peso;
	}
	memset(dp,-1,sizeof(dp));
	printf("%d\n",solve(0,1));
	return 0;
}