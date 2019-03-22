#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;
const int mod = 1e9 + 7;

vector<int> gph[MAXN];
int n, k;
int sz[MAXN], upK[MAXN], dp[MAXN];
int ret = 0;

void solve(int x, int p){
	dp[x] = upK[x];
	vector<int> mxes;
	for(auto &i : gph[x]){
		if(i != p){
			solve(i, x);
			dp[x] = max(dp[x], dp[i] + upK[x] - (sz[i] >= k));
			mxes.push_back(dp[i] - (sz[i] >= k ? 1 : 0));
			ret = max(ret, dp[i] + upK[x] - (sz[i] >= k) + (x != 1 && sz[x] <= n - k));
		}
	}
	sort(mxes.rbegin(), mxes.rend());
	if(mxes.size() >= 2){
		ret = max(ret, mxes[0] + mxes[1] + (x != 1 && sz[x] <= n - k) + upK[x]);
	}
}

void dfs(int x, int p){
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x);
			sz[x] += sz[i];
			if(sz[i] >= k) upK[x]++;
		}
	}
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	solve(1, -1);
	cout << ret << endl;
}
