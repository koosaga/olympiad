// Ivan Carvalho
// Solution to https://www.spoj.com/problems/EDIST/
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MAXN 2010
using namespace std;
char entrada1[MAXN], entrada2[MAXN];
int dp[MAXN][MAXN];
int main(){
	int testes;
	scanf("%d",&testes);
	while(testes--){
		memset(dp,0,sizeof(dp));
		scanf("%s",entrada1);
		scanf("%s",entrada2);
		int tam1 = strlen(entrada1) , tam2 = strlen(entrada2);
		for(int i=0;i<=tam1;i++) dp[i][0] = i;
		for(int i=0;i<=tam2;i++) dp[0][i] = i;
		for(int i=1;i<=tam1;i++){
			for(int j=1;j<=tam2;j++){
				dp[i][j] = dp[i-1][j-1] + (entrada1[i-1] == entrada2[j-1] ? 0 : 1);
				dp[i][j] = min(dp[i][j],dp[i-1][j]+1);
				dp[i][j] = min(dp[i][j],dp[i][j-1]+1);
			}
		}
		printf("%d\n",dp[tam1][tam2]);
	}
	return 0;
}