// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc07s5
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[30002][501];
int soma[30002];
int n,w,k;
int custo(int i,int j){
	return soma[j] - soma[i-1];
}
int solve(int pos,int restam){
	if(pos > n || restam == 0) return 0;
	if(dp[pos][restam] != -1) return dp[pos][restam];
	if(pos + w - 1 >= n){
		return dp[pos][restam] = custo(pos, min(pos+w - 1,n));
	}
	return dp[pos][restam] = max( solve(pos+1,restam), custo(pos,pos+w - 1) + solve(pos+w,restam-1) );
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		memset(dp,-1,sizeof(dp));
		scanf("%d %d %d",&n,&k,&w);
		for(int i=1;i<=n;i++){
			scanf("%d",&soma[i]);
			soma[i]+=soma[i-1];
		}
		printf("%d\n",solve(1,k));
	}
	return 0;
}