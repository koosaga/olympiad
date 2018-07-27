#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200005;

struct mtrx{
	int adj[2][2];
	mtrx(){}
	mtrx(int x){
		if(x == 0){
			adj[0][0] = adj[1][1] = 0;
			adj[1][0] = adj[0][1] = 1;
		}
		else{
			adj[0][0] = adj[1][1] = 1e9;
			adj[1][0] = adj[0][1] = 1e9;
		}
	}
}val[18][MAXN];

mtrx mul(mtrx a, mtrx b){
	mtrx c(1e9);
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			for(int k=0; k<2; k++){
				c.adj[j][k] = min(a.adj[j][i] + b.adj[i][k], c.adj[j][k]);
			}
		}
	}
	return c;
}

#define floor fuck 
int n, k, q, a[MAXN];
vector<int> upd[MAXN];
vector<int> gph[MAXN];
int par[18][MAXN], dep[MAXN], din[MAXN], dout[MAXN], piv;

pi intv[MAXN];
int floor[MAXN], vtx;
map<pi, int> mp;

bool in(int s, int e){
	return din[s] <= din[e] && dout[e] <= dout[s];
}

int anc(int x, int v){
	for(int i=0; i<18; i++){
		if((v >> i) & 1) x = par[i][x];
	}
	return x;
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	e = anc(e, dep[e] - dep[s]);
	for(int i=17; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

mtrx path(int x, int v){
	if(v == 0){
		mtrx mtx(0);
		return mtx;
	}
	mtrx mtx(0);
	for(int i=0; i<18; i++){
		if((v >> i) & 1){
			mtx = mul(mtx, val[i][x]);
			x = par[i][x];
		}
	}
	return mtx;
}

int query_intv(pi s, pi e){
	if(s.first == e.first) return s.second == e.second ? 0 : 1;
	if(s > e) swap(s, e);
	if(in(s.first, e.first)){
		mtrx ans = path(e.first, dep[e.first] - dep[s.first]);
		return ans.adj[e.second][s.second];
	}
	else{
		auto count = [&](int s, int l, int r){
			return upper_bound(upd[s].begin(), upd[s].end(), r) - lower_bound(upd[s].begin(), upd[s].end(), l);
		};
		int l = lca(s.first, e.first);
		int ns = anc(s.first, dep[s.first] - dep[l] - 1);
		int ne = anc(e.first, dep[e.first] - dep[l] - 1);
		if(intv[ns] > intv[ne]){
			swap(ns, ne);
			swap(s, e);
		}
		mtrx lef = path(s.first, dep[s.first] - dep[l] - 1);
		mtrx rig = path(e.first, dep[e.first] - dep[l] - 1);
		int middle_dist = count(floor[ns], intv[ns].second, intv[ne].first) - 1;
		int total_dist = 2 + count(floor[ns], intv[l].first, intv[l].second);
		return min(lef.adj[s.second][0] + rig.adj[e.second][1] + total_dist - middle_dist - 2,
				   lef.adj[s.second][1] + rig.adj[e.second][0] + middle_dist);
	}
}

int query(int s, int e){
	if(s == e) return 0;
	vector<pi> src, snk;
	if(s > 1) src.emplace_back(mp[pi(s-1, s)], 1);
	else src.emplace_back(mp[pi(s, s+1)], 0);
	if(e > 1) snk.emplace_back(mp[pi(e-1, e)], 1);
	else snk.emplace_back(mp[pi(e, e+1)], 0);
	int ans = 1e9;
	for(auto &i : src) for(auto &j : snk){
		ans = min(ans, query_intv(i, j));
	}
	return ans;
}

void dfs(int x){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		dep[i] = dep[x] + 1;
		dfs(i);
	}
	dout[x] = piv;
}

int main(){
	scanf("%d %d %d",&n,&k,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		if(i > 1 && i < n) upd[a[i]].push_back(i);
	}
	if(n == 2){
		while(q--){
			puts("0");
		}
		return 0;
	}
	set<int> s;
	s.insert(1);
	s.insert(n);
	mp[pi(1, n)] = 0;
	intv[0] = pi(1, n);
	floor[0] = k;
	for(int i=k; i; i--){
		for(int j=0; j<upd[i].size(); ){
			int st = *--s.lower_bound(upd[i][j]);
			int ed = *s.lower_bound(upd[i][j]);
			int e = j;
			while(e < upd[i].size() && upd[i][e] < ed){
				e++;
			}
			int cur_vtx = mp[pi(st, ed)];
			mp.erase(pi(st, ed));
			vector<pi> sons;
			sons.emplace_back(st, upd[i][j]);
			for(int k=j+1; k<e; k++){
				sons.emplace_back(upd[i][k-1], upd[i][k]);
			}
			sons.emplace_back(upd[i][e-1], ed);
			for(int k=0; k<sons.size(); k++){
				int tmp[4][4] = {};
				tmp[0][2] = tmp[2][0] = k;
				tmp[0][3] = tmp[3][0] = sons.size() - k;
				tmp[1][2] = tmp[2][1] = k + 1;
				tmp[1][3] = tmp[3][1] = sons.size() - k - 1;
				tmp[0][1] = tmp[1][0] = tmp[2][3] = tmp[3][2] = 1;
				for(int i=0; i<4; i++){
					for(int j=0; j<4; j++){
						for(int k=0; k<4; k++){
							tmp[j][k] = min(tmp[j][k], tmp[j][i] + tmp[i][k]);
						}
					}
				}
				vtx++;
				mp[sons[k]] = vtx;
				intv[vtx] = sons[k];
				par[0][vtx] = cur_vtx;
				floor[vtx] = i;
				val[0][vtx].adj[0][0] = tmp[0][2];
				val[0][vtx].adj[0][1] = tmp[0][3];
				val[0][vtx].adj[1][0] = tmp[1][2];
				val[0][vtx].adj[1][1] = tmp[1][3];
			}
			j = e;
		}
		for(auto &j : upd[i]){
			s.insert(j);
		}
	}
	for(int i=1; i<=vtx; i++) gph[par[0][i]].push_back(i);
	dfs(0);
	for(int i=1; i<18; i++){
		for(int j=1; j<=vtx; j++){
			if(dep[j] < (1<<i)) continue;
			par[i][j] = par[i-1][par[i-1][j]];
			val[i][j] = mul(val[i-1][j], val[i-1][par[i-1][j]]);
		}
	}
	while(q--){
		int l, r;
		scanf("%d %d",&l,&r);
		if(l > r) swap(l, r);
		auto v = lower_bound(upd[k].begin(), upd[k].end(), l);
		auto w = upper_bound(upd[k].begin(), upd[k].end(), r);
		if(v == w){
			printf("%d\n", query(l, r) - 1);
		}
		else{
			w--;
			printf("%d\n", query(l, *v) + query(*w, r) + (int)(w - v) - 1);
		}
	}
}
