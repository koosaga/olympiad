// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1224
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
using namespace std;
typedef long long ll;
inline int mod(int x){
	return ((x % 3) + 3) % 3;
}
ll vetor[MAXN],dp[MAXN][3];
int n;
ll solve(){
	for(int fim = 1;fim <= n;fim++){
		for(int ini = n;ini >= 1;ini--){
			if(fim < ini) dp[ini][mod(fim)] = 0;
			if(fim>ini) dp[ini][mod(fim)]=max(vetor[ini]+min(dp[ini+2][mod(fim)], dp[ini+1][mod(fim-1)]), vetor[fim]+min(dp[ini+1][mod(fim-1)], dp[ini][mod(fim-2)]));
		}
	}
	return dp[1][mod(n)];
}
int main(){
	while(scanf("%d",&n) != EOF){
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++){
			scanf("%lld",&vetor[i]);
		}
		printf("%lld\n",solve());
	}
	return 0;
}
