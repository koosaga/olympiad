#include "split.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
using pi = pair<int, int>;
const int MAXN = 100005;

int n;
vector<int> gph[MAXN];
vector<int> tr[MAXN];

namespace report{
	vector<int> gph[MAXN];
	int mark[MAXN], vis[MAXN];
	void dfs(int x, vector<int> &dfn){
		dfn.push_back(x);
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(mark[x] == mark[i] && !vis[i]){
				dfs(i, dfn);
			}
		}
	}
	vector<pi> color;
	vector<int> Do(vector<int> S){
		for(auto &i : S) mark[i] = 1;
		vector<int> ans(n, color[2].second);
		for(int i=0; i<n; i++){
			vector<int> dfn;
			if(mark[i] == 1 && !vis[i]){
				dfs(i, dfn);
				for(int j=0; j<color[0].first; j++){
					ans[dfn[j]] = color[0].second;
				}
			}
			if(mark[i] == 0 && !vis[i]){
				dfs(i, dfn);
				for(int j=0; j<color[1].first; j++){
					ans[dfn[j]] = color[1].second;
				}
			}
		}
		return ans;
	}
}

struct disj{
	int pa[MAXN], sz[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(sz, sz + n + 1, 1);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	int getsz(int x){ return sz[find(x)]; }
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		sz[p] += sz[q];
		pa[q] = p; 
		return 1;
	}
}disj;

int sz[MAXN], msz[MAXN];

void dfsc(int x, int p){
	sz[x] = 1; msz[x] = 0;
	for(auto &i : tr[x]){
		if(i != p){
			dfsc(i, x);
			sz[x] += sz[i];
			msz[x] = max(msz[x], sz[i]);
		}
	}
}

int get_center(){
	dfsc(0, 0);
	pi ret(1e9, 1e9);
	for(int i=0; i<n; i++){
		ret = min(ret, pi(max(msz[i], n - sz[i]), i));
	}
	return ret.second;
}

void dfs(int x, int p, vector<int> &dfn){
	dfn.push_back(x);
	for(auto &i : tr[x]){
		if(i != p){
			disj.uni(x, i);
			dfs(i, x, dfn);
		}
	}
}

bool vis[MAXN];

void dfsa(int x, vector<int> &dfn){
	dfn.push_back(x);
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(!vis[i]) dfsa(i, dfn);
	}
}

vector<int> find_split(int _n, int a, int b, int _c, vector<int> p, vector<int> q) {
	n = _n;
	vector<pi> cs = {pi(a, 1), pi(b, 2), pi(_c, 3)};
	sort(cs.begin(), cs.end());
	report::color = cs;
	a = cs[0].first;
	disj.init(n);
	for(int i=0; i<sz(p); i++){
		if(disj.uni(p[i], q[i])){
			tr[p[i]].push_back(q[i]);
			tr[q[i]].push_back(p[i]);
		}
		report::gph[p[i]].push_back(q[i]);
		report::gph[q[i]].push_back(p[i]);
	}
	disj.init(n);
	int c = get_center();
	for(auto &i : tr[c]){
		vector<int> dfn;
		dfs(i, c, dfn);
		if(disj.getsz(i) >= a){
			return report::Do(dfn);
		}
	}
	for(int i=0; i<sz(p); i++){
		if(p[i] == c || q[i] == c) continue;
		int l = disj.find(p[i]);
		int r = disj.find(q[i]);
		if(l != r){
			gph[l].push_back(r);
			gph[r].push_back(l);
		}
	}
	for(int i=0; i<n; i++){
		if(i != c && disj.find(i) == i && !vis[i]){
			vector<int> dfn;
			dfsa(i, dfn);
			int sum = 0;
			set<int> pot;
			for(auto &i : dfn){
				sum += disj.getsz(i);
				pot.insert(i);
				if(sum >= a) break;
			}
			if(sum >= a){
				vector<int> ans;
				for(int i=0; i<n; i++){
					if(pot.find(disj.find(i)) != pot.end()){
						ans.push_back(i);
					}
				}
				return report::Do(ans);
			}
		}
	}
	return vector<int>(n, 0);
}
