// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADADUNG/
#include <cstdio>
typedef long long ll;
const ll MAXN = 1e7 + 1;
const ll MODULO = 1e9 + 7;
ll dp[MAXN];
int main(){
	dp[1] = 0;
	for(ll i=2;i<MAXN;i++){
		dp[i] = i * dp[i-1];
		if(i % 2 == 0) dp[i]++;
		else dp[i]--;
		if(dp[i] < 0) dp[i] += MODULO;
		dp[i] %= MODULO;
	}
	int TC;
	scanf("%d",&TC);
	while(TC--){
		int davez;
		scanf("%d",&davez);
		printf("%lld\n",dp[davez]);
	}
	return 0;
}