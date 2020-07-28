// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc18s4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e6 + 10;

ll dp[MAXN];
unordered_map<int,ll> tab;

ll solve(int n){
	if(n < MAXN && dp[n] != -1) return dp[n];
	else if(n >= MAXN && tab.count(n)) return tab[n];
	ll tot = 0;
	ll i = 2;
	while(i <= n){
		ll q = n/i;
		ll j = n/q;
		tot += (j - i + 1)*solve(q);
		i = j + 1;
	}
	if(n < MAXN) return dp[n] = tot;
	else return tab[n] = tot;
}

int main(){
	memset(dp,-1,sizeof(dp));
	dp[1] = 1;dp[0] = 0;
	int N;
	cin >> N;
	cout << solve(N) << endl;
	return 0;
}