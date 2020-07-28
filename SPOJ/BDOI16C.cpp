// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BDOI16C/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2001;
const int MAXC = 3001;
const int MOD = 10007;
int dp[2][MAXC];
int somatorio[MAXC];
int solve(int n,int k){
	if(k < 0) return 0;
	memset(dp,0,sizeof(dp));
	memset(somatorio,0,sizeof(somatorio));
	dp[1][0] = 1;dp[1][1] = 0;
	for(int vez = 2;vez<=n;vez++){
		for(int i = 0;i<=k;i++){
			dp[0][i] = dp[1][i];
			somatorio[i] = dp[0][i];
			dp[1][i] = 0;
		}
		for(int i = 1;i<=k;i++){
			somatorio[i] += somatorio[i-1];
			somatorio[i] %= MOD;
		}
		for(int i = 0;i<=k;i++){
			int hi = i;
			int lo = i - min(i,vez-1);
			int val = somatorio[hi];
			if(lo != 0) val -= somatorio[lo - 1];
			val %= MOD;
			dp[1][i] = val;
		}
		for(int i = (vez*(vez-1))/2 + 1;i<=k;i++){
			dp[1][i] = 0;
		}
	}
	int tot = 0;
	for(int i = 0;i<=k;i++) tot = (tot + dp[1][i]);
	return tot % MOD;
}
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc = 1;tc<=TC;tc++){
		int n,k;
		scanf("%d %d",&n,&k);
		int fat = 1;
		for(int i = 2;i<=n;i++){
			fat *= i;
			fat %= MOD;
		}
		fat -= solve(n,k-1);
		if(fat < 0) fat += MOD;
		fat %= MOD;
		printf("Case %d: %d\n",tc,fat);
	}
	return 0;
}