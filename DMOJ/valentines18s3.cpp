// Ivan Carvalho
// Solution to https://dmoj.ca/problem/valentines18s3
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 102;
const int MOD = 1e9 + 7;

ll dp[MAXN][MAXN][MAXN]; // position, last, biggest
int N,K;

ll solve(int pos,int last,int seq_sz){

	if(dp[pos][last][seq_sz] != -1) return dp[pos][last][seq_sz];

	if(last > pos || seq_sz > K || seq_sz > pos) return dp[pos][last][seq_sz] = 0;

	if(pos == 1){
		return dp[pos][last][seq_sz] = 1;
	}

	ll tot = 0;

	if(seq_sz == 1){
		for(int tam = 1;tam<=K;tam++){
			for(int nxt = last;nxt<=pos-1;nxt++){
				tot += solve(pos-1,nxt,tam);
			}
			tot %= MOD;
		}
	}
	else{
		for(int nxt = 1;nxt<last;nxt++){
			tot += solve(pos-1,nxt,seq_sz - 1);
		}
	}

	return dp[pos][last][seq_sz] = (tot % MOD);

}

int main(){

	cin >> N >> K;

	memset(dp,-1,sizeof(dp));
	ll tot_b = 0;
	for(int last = 1;last<=N;last++){
		for(int last_sz = 1;last_sz<=K;last_sz++){
			tot_b = (tot_b + solve(N,last,last_sz)) % MOD;
		}
	}

	K--;
	memset(dp,-1,sizeof(dp));
	ll tot_a = 0;
	for(int last = 1;last<=N;last++){
		for(int last_sz = 1;last_sz<=K;last_sz++){
			tot_a = (tot_a + solve(N,last,last_sz)) % MOD;
		}
	}

	ll tot = tot_b - tot_a;
	tot = (tot + MOD) % MOD;
	cout << tot << endl;

	return 0;

}