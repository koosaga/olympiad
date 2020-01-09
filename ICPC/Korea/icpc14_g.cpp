#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 30005;

int n, c;

struct edg{
	int pos, x, y;
};

vector<edg> gph[MAXN];
int dep[MAXN], cst[MAXN], idx[MAXN];

void dfs(int x, int p){
	idx[x] = x;
	for(auto &i : gph[x]){
		if(i.pos != p){
			dep[i.pos] = dep[x] + i.x;
			cst[i.pos] = cst[x] + i.y;
			dfs(i.pos, x);
		}
	}
}

set<pi> ms[MAXN];

int merge(int x, int y){
	int d = c + dep[y] + dep[y];
	int cc = cst[y] * 2;
	if(sz(ms[idx[x]]) < sz(ms[idx[y]])) swap(x, y);
	int ret = 0;
	for(auto &i : ms[idx[y]]){
		auto w = ms[idx[x]].upper_bound(pi(d - i.first + 1, -1));
		if(w != ms[idx[x]].begin()){
			ret = max(ret, i.second + prev(w)->second - cc);
		}
	}
	for(auto &i : ms[idx[y]]){
		auto w = ms[idx[x]].upper_bound(pi(i.first + 1, -1));
		if(w != ms[idx[x]].begin() && prev(w)->second >= i.second) continue;
		w = ms[idx[x]].lower_bound(pi(i.first, -1));
		while(w != ms[idx[x]].end() && w->second <= i.second){
			w = ms[idx[x]].erase(w);
		}
		ms[idx[x]].insert(i);
	}
	idx[y] = idx[x];
	return ret;
}

int solve(int x, int p){
	ms[x].emplace(dep[x], cst[x]);
	int ret = 0;
	for(auto &i : gph[x]){
		if(i.pos != p){
			ret = max(ret, solve(i.pos, x));
			ret = max(ret, merge(i.pos, x));
		}

	}
	return ret;
}

void solve(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int u, v, x, y; scanf("%d %d %d %d",&u,&v,&x,&y);
		gph[u].push_back({v, x, y});
		gph[v].push_back({u, x, y});
	}
	cin >> c;
	dfs(1, 0);
	cout << solve(1, 0) << endl;
	for(int i=0; i<=n; i++){
		gph[i].clear();
		ms[i].clear();
	}
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
}
