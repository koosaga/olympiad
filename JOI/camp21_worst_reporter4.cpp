#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

const int MAXN = 200005;

vector<int> gph[MAXN];
map<lint, lint> s[MAXN];
int n, v[MAXN], c[MAXN], par[MAXN];
int dp[MAXN], indeg[MAXN];

void dfs(int i){
	int x = i;
	dp[x] = -1;
	for(auto &i : gph[x]){
		if(indeg[i]) continue;
		dfs(i);
		if(dp[x] == -1 || s[dp[i]].size() > s[dp[x]].size()){
			dp[x] = dp[i];
		}
	}
	if(dp[x] == -1) dp[x] = x;
	for(auto &i : gph[x]){
		if(indeg[i]) continue;
		if(dp[i] != dp[x]){
			for(auto &[v, w] : s[dp[i]]){
				s[dp[x]][v] += w;
			}
		}
	}
	if(!indeg[i]){
		int val = c[i];
		auto l = s[dp[x]].upper_bound(v[i]);
		while(val && l != s[dp[x]].end()){
			if(val >= l->second){
				val -= l->second;
				l = s[dp[x]].erase(l);
			}
			else{
				auto foo = *l;
				l = s[dp[x]].erase(l);
				foo.second -= val;
				s[dp[x]].insert(foo);
				val = 0;
			}
		}
	}
	if(!indeg[i]) s[dp[i]][v[i]] += c[i];
}

int main(){
	scanf("%d",&n);
	lint sum = 0;
	for(int i=1; i<=n; i++){
		scanf("%d %d %d",&par[i],&v[i],&c[i]);
		v[i] = 1000000000 - v[i];
		sum += c[i];
		gph[par[i]].push_back(i);
		indeg[par[i]]++;
	}
	queue<int> que;
	for(int i = 1; i <= n; i++){
		if(!indeg[i]){
			que.push(i);
		}
	}
	while(sz(que)){
		int x = que.front();
		que.pop();
		indeg[par[x]]--;
		if(!indeg[par[x]]) que.push(par[x]);
	}
	for(int i = 1; i <= n; i++){
		if(indeg[i] == 0) continue;
		vector<int> cyc = {i};
		for(int j = par[i]; j != i; j = par[j]){
			cyc.push_back(j);
		}
		vector<pi> vect;
		map<lint, lint> mp;
		mp[-1] = 0;
		mp[2e9] = 0;
		for(auto &j : cyc){
			dfs(j);
			for(auto &[x, y] : s[dp[j]]){
				vect.emplace_back(x, y);
			}
			mp[v[j]] += c[j];
		}
		sort(all(vect));
		for(int i = sz(vect) - 2; i >= 0; i--){
			vect[i].second += vect[i + 1].second;
		}
		lint dap = 0;
		for(auto &[x, y] : mp){
			auto it = lower_bound(all(vect), pi(x + 1, -1));
			lint sum = y + (sz(vect) ? vect[0].second : 0);
			if(it != vect.end()){
				sum -= min(y, it->second);
			}
			dap = max(dap, sum);
		}
		sum -= dap;
		for(auto &j : cyc) indeg[j] = 0;
	}
	cout << sum << endl;
}
