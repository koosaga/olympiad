// Ivan Carvalho
// Solution to https://dmoj.ca/problem/lcs
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int vetor[1010][2],dp[1010][1010],n,m;
int lcs(int a,int b){
	if(a == 0 || b == 0) return dp[a][b] = 0;
	if(dp[a][b] != -1) return dp[a][b];
	if(vetor[a][0] == vetor[b][1]) return 1 + lcs(a-1,b-1);
	return dp[a][b] = max(lcs(a-1,b),lcs(a,b-1));
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&vetor[i][0]);
	for(int i=1;i<=m;i++) scanf("%d",&vetor[i][1]);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",lcs(n,m));
	return 0;
}