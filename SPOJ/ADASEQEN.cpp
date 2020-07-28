// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADASEQEN/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e3 + 10;
int dp[MAXN][MAXN];
int v1[MAXN],v2[MAXN];
int val[MAXN];
int n,m;
char s1[MAXN],s2[MAXN];
int solve(int a,int b){
	if(!a || !b){
		return 0;
	}
	if(dp[a][b] != -1) return dp[a][b];
	int ret = 0;
	if(v1[a] == v2[b]) ret = val[v1[a]] + solve(a-1,b-1);
	return dp[a][b] = max(ret, max(solve(a,b-1),solve(a-1,b)));
}
int main(){
	scanf("%d %d",&n,&m);
	memset(dp,-1,sizeof(dp));
	for(int i = 0;i<26;i++){
		scanf("%d",&val[i]);
	}
	scanf("%s",s1);
	scanf("%s",s2);
	for(int i = 1;i<=n;i++){
		v1[i] = s1[i-1] - 'a';
	}
	for(int i = 1;i<=m;i++){
		v2[i] = s2[i-1] - 'a';
	}
	printf("%d\n",solve(n,m));
	return 0;
} 