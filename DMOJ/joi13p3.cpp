// Ivan Carvalho
// Solution to https://dmoj.ca/problem/joi13p3
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2010;
vector<ll> V;
ll dp[MAXN][MAXN],nxt[MAXN][2],N,P,Q,W;
ll solve(ll pos,ll resta){
	if(dp[pos][resta] != -1) return dp[pos][resta];
	if(pos == N) return 0;
	ll best = 1 + solve(nxt[pos][0]+1,resta);
	if(resta != 0) best = min(best, solve(nxt[pos][1] + 1,resta - 1) );
	return dp[pos][resta] = best;
}
ll check(ll val){
	W = val;
	memset(dp,-1,sizeof(dp));
	for(ll i = 0;i<N;i++){
		nxt[i][0] = prev(upper_bound(V.begin(),V.end(),V[i] + W - 1)) - V.begin();
		nxt[i][1] = prev(upper_bound(V.begin(),V.end(),V[i] + 2*W - 1)) - V.begin();
	}
	return solve(0,Q) <= P;
}
int main(){
	cin >> N >> P >> Q;
	for(ll i = 0;i<N;i++){
		ll x;
		cin >> x;
		V.push_back(x);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	N = V.size();
	P = min(P,N);
	Q = min(Q,N);
	ll ini = 1,fim = (ll)1e9,meio,resp = -1;
	while(ini <= fim){
		meio = ini + (fim - ini)/2;
		if(check(meio)){
			resp = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}
	cout << resp << endl;
	return 0;
}
