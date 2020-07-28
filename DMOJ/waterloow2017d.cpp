// Ivan Carvalho
// Solution to https://dmoj.ca/problem/waterloow2017d
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 31;
const int MAXK = 901;
const int MOD = 1e9 + 7;

ll dp[MAXN][MAXK],cof[MAXN][MAXN];
int N,K,limit[MAXN];

ll binomial(int n,int k){

	if(k > n) return 0;
	if(cof[n][k] != -1) return cof[n][k];
	if(k == 0) return cof[n][k] = 1; 

	return cof[n][k] = (binomial(n-1,k) + binomial(n-1,k-1)) % MOD;

}

ll solve(int n,int k){

	if(k - n < 0) return 0;
	if(k - n > limit[n] ) return 0;
	if(dp[n][k] != -1) return dp[n][k];
	if(n == 1) return dp[n][k] = (k == 1);
	if(n == 0) return dp[n][k] = (k == 0);

	int t = k - n;
	ll tot = 0;
	for(int m = 1;m<=n;m++){
		for(int l = m-1;l<=t;l++){
			tot = (tot + (solve(m - 1,l)*binomial(n-1,m-1) % MOD)*solve(n - m,t - l)) % MOD;
		}
	}

	return dp[n][k] = tot;

}

int main(){

	memset(dp,-1,sizeof(dp));
	memset(cof,-1,sizeof(cof));
	
	cin >> N >> K;
	for(int i = 1;i<=N;i++){
		limit[i] = (i*(i-1))/2;
	}
	cout << solve(N,K) << endl;

	return 0;

}