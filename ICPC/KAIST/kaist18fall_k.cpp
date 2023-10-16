#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 250005;

int n, k;
vector<pi> gph[MAXN];
pi dp[MAXN][2];

void dfs(int x, int p, lint m){
	pi one_up(0, 0), sum(0, 0);
	for(auto &i : gph[x]){
		int v, c; tie(c, v) = i;
		if(v == p) continue;
		dfs(v, x, m);
		sum.first += dp[v][0].first;
		sum.second += dp[v][0].second;
		one_up = max(one_up, pi(dp[v][1].first - dp[v][0].first + c - m, dp[v][1].second - dp[v][0].second + 1));
	}
	dp[x][1] = sum;
	dp[x][0] = pi(sum.first + one_up.first, sum.second + one_up.second);
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n-1; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	dfs(1, 0, -1e12);
	if(dp[1][0].second < k){
		puts("Impossible");
		return 0;
	}
	lint s = -1e12, e = 1e12;
	while(s != e){
		lint m = s + (e - s + 1) / 2;
		dfs(1, 0, m);
		if(dp[1][0].second >= k) s = m;
		else e = m - 1;
	}
	dfs(1, 0, s);
	cout << dp[1][0].first + s * k << endl;
}