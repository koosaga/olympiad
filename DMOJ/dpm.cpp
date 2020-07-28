// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpm
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 1e5 + 10;
const int MOD = 1e9 + 7;

int pref[MAXK],dp[MAXK],N,K;

int calc(int a,int b){
	if(a < 0) a = 0;
	int ans = pref[b];
	if(a != 0) ans -= pref[a-1];
	return ans % MOD;
}

int main(){

	cin >> N >> K;

	dp[0] = 1;

	for(int kid = 1;kid<=N;kid++){

		int c;
		cin >> c;

		pref[0] = dp[0];
		dp[0] = 0;
		for(int i = 1;i<=K;i++){
			pref[i] = (pref[i-1] + dp[i]) % MOD;
		}

		for(int i = 0;i<=K;i++){
			dp[i] = calc(i-c,i);
		}

	}

	int ans = dp[K];
	if(ans < 0) ans += MOD; 
	printf("%d\n",ans);

	return 0;

}