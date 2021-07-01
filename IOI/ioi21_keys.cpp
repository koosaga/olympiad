#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 600005;
 
struct disj{
	int pa[MAXN];
	void init(){
		iota(pa, pa + MAXN, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;
 
set<int> keys[MAXN];
set<pi> gph[MAXN];
vector<int> canReach[MAXN];
int comp[MAXN], nxt[MAXN];
int idx[MAXN], sz[MAXN];

int find(int x){
	return comp[x] = (comp[x] == x ? x : find(comp[x]));
}

int cnt = 0;
void merge_to(int u, int v){
	u = find(u);
	cnt++;
	if(cnt >= 2000000) assert(0);
	if(u == v) return;
	comp[u] = v;
	int iu = idx[u], iv = idx[v];
	if(sz[u] > sz[v]) swap(iu, iv);
	sz[v] += sz[u];
	for(auto &i : keys[iu]){
		if(keys[iv].find(i) == keys[iv].end()){
			keys[iv].insert(i);
			auto it = gph[iv].lower_bound(pi(i, -1));
			while(it != gph[iv].end() && it->first == i){
				canReach[iv].push_back(it->second);
				it = gph[iv].erase(it);
			}
		}
	}
	for(auto &i : canReach[iu]) canReach[iv].push_back(i);
	for(auto &[c, d] : gph[iu]){
		if(keys[iv].find(c) != keys[iv].end()){
			canReach[iv].push_back(d);
		}
		else gph[iv].emplace(c, d);
	}
	keys[iu].clear();
	gph[iu].clear();
	canReach[iu].clear();
	idx[v] = iv;
}
 
std::vector<int> find_reachable(std::vector<int> r, std::vector<int> u, std::vector<int> v, std::vector<int> c) {	
	int n = sz(r);
	for(int i = 0; i < n; i++) keys[i].insert(r[i]);
	for(int i = 0; i < sz(u); i++){
		if(c[i] == r[u[i]]){
			canReach[u[i]].push_back(v[i]);
		} else{
			gph[u[i]].emplace(c[i], v[i]);
		}
		if(c[i] == r[v[i]]){
			canReach[v[i]].push_back(u[i]);
		} else {
			gph[v[i]].emplace(c[i], u[i]);
		}
	}
	disj.init();
	iota(idx, idx + MAXN, 0);
	fill(sz, sz + MAXN, 1);
	iota(comp, comp + MAXN, 0);
	vector<int> ans(n, 1e9);
	for(int i = 0; i < n; i++){
		nxt[i] = i;
		if(sz(canReach[i])) nxt[i] = canReach[i][0];
	}
	for(int i = 0; i < n; i++){
		if(find(i) != i) continue;
		if(i == find(nxt[i])) continue;
		if(!disj.uni(i, nxt[i])){
			for(int j = find(nxt[i]); find(j) != find(n); j = find(nxt[j])){
				merge_to(j, n);
			}
			disj.uni(i, n);
			nxt[n] = n;
			while(sz(canReach[idx[n]]) && find(canReach[idx[n]].back()) == find(n)){
				canReach[idx[n]].pop_back();
			}
			if(sz(canReach[idx[n]])) nxt[n] = canReach[idx[n]].back();
			n++;
			assert(n <= 600000);
		}
	}
	vector<int> cnt(n);
	for(int j = 0; j < sz(ans); j++){
		cnt[find(j)]++;
	}
	fill(all(ans), 1e9);
	for(int i = 0; i < sz(ans); i++){
		int r = find(i);
		if(find(r) == find(nxt[r])) ans[i] = cnt[r];
	}
	int val = *min_element(all(ans));
	for(auto &i : ans){
		i = (i == val);
	}
	return ans;
}


