#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())

vector<int> gph[MAXN];
vector<pi> info[MAXN];
int n, m, par[MAXN], a[MAXN], dep[MAXN];
map<lint, lint> v[MAXN];

void solve(){
	scanf("%d %d",&n,&m);
	for(int i=2; i<=n; i++) scanf("%d",&par[i]);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		gph[par[i]].push_back(i);
		dep[i] = dep[par[i]] + 1;
	}
	for(int i=1; i<=m; i++){
		int x, k, c;
		scanf("%d %d %d",&x,&k,&c);
		info[x].push_back(pi(k + 1, c));
	}
	vector<int> idx(n + 1);
	iota(idx.begin(), idx.end(), 0);
	for(int i=n; i>=0; i--){
		if(sz(gph[i]) == 0){
			v[idx[i]][dep[i]] += a[i];
		}
		else{
			pi ret(-1, -1);
			for(auto &j : gph[i]){
				ret = max(ret, pi(sz(v[idx[j]]), j));
			}
			idx[i] = idx[ret.second];
			for(auto &j : gph[i]){
				if(j == ret.second) continue;
				for(auto &k : v[idx[j]]){
					v[idx[i]][k.first] += k.second;
				}
			}
			v[idx[i]][dep[i]] += a[i];
		}
		for(auto &j : info[i]){
			int arg = dep[i] + j.first;
			auto l = v[idx[i]].lower_bound(arg);
			while(j.second > 0 && l != v[idx[i]].begin()){
				lint delta = min(j.second, prev(l)->second);
				prev(l)->second -= delta;
				j.second -= delta;
				if(prev(l)->second == 0){
					v[idx[i]].erase(prev(l));
				}
			}
		}
	}
	lint ret = 0;
	for(auto &i : v[idx[0]]) ret += i.second;
	printf("%lld\n", ret);
}

int main(){
	int t; cin >> t;
	while(t--){
		solve();
		for(int i=0; i<=n; i++){
			gph[i].clear();
			info[i].clear();
			v[i].clear();
		}
	}
}
