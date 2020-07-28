// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SCUBADIV/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1002;
const int MAXO = 24;
const int MAXNI = 81;
const int INF = 1e5;
int dp[MAXN][MAXO][MAXNI];
int qualvez,a,b,resetou[MAXN][MAXO];
int v1[MAXN],v2[MAXN],cost[MAXN];
int n;
int solve(int pos,int oxygen,int nitrogen){
	oxygen = max(oxygen,0);nitrogen = max(nitrogen,0);
	if(oxygen == 0 && nitrogen == 0) return 0;
	if(pos > n){
		return INF;
	}
	if(dp[pos][oxygen][nitrogen] != -1) return dp[pos][oxygen][nitrogen];
	return dp[pos][oxygen][nitrogen] = min(solve(pos+1,oxygen - v1[pos],nitrogen - v2[pos]) + cost[pos], solve(pos+1,oxygen,nitrogen) );
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		memset(dp,-1,sizeof(dp));
		scanf("%d %d",&a,&b);
		scanf("%d",&n);
		for(int i = 1;i<=n;i++) scanf("%d %d %d",&v1[i],&v2[i],&cost[i]);
		printf("%d\n",solve(1,a,b));
	}
	return 0;
} 