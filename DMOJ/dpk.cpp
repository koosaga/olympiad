// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpk
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 1e5 + 10;
const int MAXN = 1e3 + 10;

int A[MAXN],dp[MAXK],N,K;

int solve(int k){

	if(dp[k] != -1) return dp[k];

	if(k == 0) return dp[k] = 0;

	int ans = 0;
	for(int i = 1;i<=N;i++){
		if(A[i] > k) continue;
		if(solve(k - A[i]) == 0){
			ans = 1;
			break;
		}
	}

	return dp[k] = ans;

}

int main(){

	memset(dp,-1,sizeof(dp));
	cin >> N >> K;
	for(int i = 1;i<=N;i++){
		cin >> A[i];
	}

	if(solve(K)) printf("First\n");
	else printf("Second\n");

	return 0;

}