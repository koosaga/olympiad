// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c4p6
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 310;
const ll INF = 1e17;

ll dp[MAXN][MAXN][2][2][2][2],A,B,K;

inline ll sq(ll x){return x*x;}

ll solve(ll a,ll b,ll w1,ll w2,ll w3,ll w4){
	if(w1 == 0 && w2 == 1){
		swap(w1,w2);
	}
	if(w3 == 0 && w4 == 1){
		swap(w3,w4);
	}
	if(a > b){
		swap(a,b);
		swap(w1,w3);
		swap(w2,w4);
	}
	if(dp[a][b][w1][w2][w3][w4] != -1) return dp[a][b][w1][w2][w3][w4];
	if(w1 + w2 + w3 + w4 == 0) return dp[a][b][w1][w2][w3][w4] = INF;
	ll best = sq(a*b - K);
	for(ll quebra = 1;quebra < a;quebra++){
		ll v1 = solve(quebra,b,w1 & 1,0,w3,w4);
		ll v2 = solve(a - quebra,b,0,w2 & 1,w3,w4);
		best = min(best,v1 + v2);
	}
	for(ll quebra = 1;quebra<b;quebra++){
		ll v1 = solve(a,quebra,w1,w2,w3 & 1,0);
		ll v2 = solve(a,b - quebra,w1,w2,0,w4 & 1);
		best = min(best,v1 + v2);
	}
	return dp[a][b][w1][w2][w3][w4] = best;
}

int main(){
	cin >> A >> B >> K;
	memset(dp,-1,sizeof(dp));
	cout << solve(A,B,1,1,1,1) << endl;
	return 0;
}