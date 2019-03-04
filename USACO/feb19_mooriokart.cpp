#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 2505;
const int mod = 1e9 + 7;

vector<pi> gph[MAXN];
bool vis[MAXN];

void ndfs(int x, int p, int d, vector<int> &store){
	if(~p) store.push_back(d);
	for(auto &i : gph[x]){
		if(i.second != p) ndfs(i.second, x, d + i.first, store);
	}
}

void dfs(int x, int p, vector<int> &store){
	vis[x] = 1;
	ndfs(x, -1, 0, store);
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dfs(i.second, x, store);
	}
}

pi dp[MAXN];
pi ndp[MAXN];
int main(){
	freopen("mooriokart.in", "r", stdin);
	freopen("mooriokart.out", "w", stdout);
	int n, m, x, y;
	scanf("%d %d %d %d",&n,&m,&x,&y);
	for(int i=1; i<=m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	vector<vector<int>> seq;
	int cmp = 0;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			vector<int> vect;
			dfs(i, -1, vect);
			seq.push_back(vect);
			y -= x;
			cmp++;
		}
	}
	y = max(y, 0); // dist requirement
	dp[0] = pi(0, 1);
	for(auto &i : seq){
		fill(ndp, ndp + y + 1, pi(0, 0));
		int cnt[MAXN] = {};
		int gyesu[MAXN] = {};
		for(auto &k : i){
			cnt[min(k, y)]++;
			gyesu[min(k, y)] += k + x;
			gyesu[min(k, y)] %= mod;
		}
		vector<int> meaningful;
		for(int j=0; j<=y; j++) if(cnt[j]) meaningful.push_back(j);
		for(int j=0; j<=y; j++){
			for(auto &k : meaningful){
				ndp[j].first += dp[max(j - k, 0)].first * cnt[k] + dp[max(j - k, 0)].second * gyesu[k];
				ndp[j].second += dp[max(j - k, 0)].second * cnt[k];
				ndp[j].first %= mod;
				ndp[j].second %= mod;
			}
		}
		for(int j=0; j<=y; j++) dp[j] = ndp[j];
	}
	lint ret = dp[y].first;
	for(int j=1; j<=cmp - 1; j++) ret = ret * j % mod;
	ret = ret * ((mod + 1) / 2) % mod;
	cout << ret << endl;
}
