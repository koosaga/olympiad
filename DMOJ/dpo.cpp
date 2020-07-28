// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpo
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 21;
const int MAXL = (1 << 21 ) + 2;
const int MOD = 1e9 + 7;

int dp[MAXN][MAXL],mascara[MAXN],N;

int solve(int pos,int bitmask){

	if(pos == N) return (__builtin_popcount(bitmask) == N);
	if(dp[pos][bitmask] != -1) return dp[pos][bitmask];

	int tot = 0;
	for(int i = 0;i<N;i++){
		if(!(bitmask & (1 << i)) && ((1 << i) & mascara[pos])){
			tot = (tot + solve(pos+1, bitmask | (1 << i) )) % MOD;
		}
	}

	return dp[pos][bitmask] = tot;

}

int main(){

	memset(dp,-1,sizeof(dp));
	cin >> N;
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N;j++){
			int x;
			cin >> x;
			if(x) mascara[i] |= (1 << j);
		}
	}
	cout << solve(0,0) << endl;

	return 0;

}