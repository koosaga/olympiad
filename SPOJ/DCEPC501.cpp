// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DCEPC501/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
ll dp[MAXN],vetor[MAXN],N,TC;
ll solve(ll a){
	if(a > N) return 0;
	if(dp[a] != -1) return dp[a];
	ll cand = vetor[a] + solve(a+2);
	if(a + 1 <= N) cand = max(cand, vetor[a] + vetor[a+1] + solve(a+4) );
	if(a + 2 <= N) cand = max(cand, vetor[a] + vetor[a+1] + vetor[a+2] + solve(a+6) );
	return dp[a] = cand;
}
int main(){
	scanf("%lld",&TC);
	while(TC--){
		scanf("%lld",&N);
		for(int i = 1;i<=N;i++){
			dp[i] = -1;
			scanf("%lld",&vetor[i]);
		}
		printf("%lld\n",solve(1));
	}
	return 0;
}