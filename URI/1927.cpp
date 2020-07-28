// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1927
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 2001
#define MAXC 21
int dp[MAXC][MAXC][MAXN],trufas[MAXC][MAXC][MAXN],n;
int func(int x, int y, int t){
	if (x < 0 || y < 0 || x > 20 || y > 20 || t > 1000) return 0;
	if (dp[x][y][t] != -1) return dp[x][y][t];
	int val = func(x-1,y,t+1);
	val = max(val,func(x+1,y,t+1));
	val = max(val,func(x,y-1,t+1));
	val = max(val,func(x,y+1,t+1));
	val = max(val,func(x,y,t+1));
	return dp[x][y][t] = trufas[x][y][t] + val;
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int u,v,k;
		scanf("%d %d %d",&u,&v,&k);
		trufas[u][v][k]++;
	}
	printf("%d\n",func(6,6,0));
	return 0;
}
