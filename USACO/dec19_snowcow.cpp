#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;
const int MAXT = 270000;

int n, q;
set<pi> intv[MAXN];

struct seg{
	int lazy[MAXT];
	lint tree[MAXT];
	void lazydown(int p, int s, int e){
		int m = (s+e)/2;
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		tree[2*p] += 1ll * (m - s + 1) * lazy[p];
		tree[2*p+1] += 1ll * (e - m) * lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int x, int ps = 0, int pe = n, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += (pe - ps + 1) * x;
			lazy[p] += x;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p, ps, pe);
		add(s, e, x, ps, pm, 2*p);
		add(s, e, x, pm+1, pe, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	lint query(int s, int e, int ps = 0, int pe = n, int p = 1){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps+pe)/2;
		lazydown(p, ps, pe);
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
}seg;

void insert(int v, int s, int e){
	auto it = intv[v].upper_bound(pi(s, -1));
	if(it != intv[v].begin() && prev(it)->second >= s){
		it = prev(it);
	}
	if(it != intv[v].end() && it->first <= s && it->second >= e){
		return;
	}
	int ns = s, ne = e;
	while(it != intv[v].end() && it->first <= e){
		ns = min(ns, it->first);
		ne = max(ne, it->second);
		seg.add(it->first, it->second, -1);
		it = intv[v].erase(it);
	}
	intv[v].emplace(ns, ne);
	seg.add(ns, ne, +1);
}

int din[MAXN], dout[MAXN], piv;
vector<int> gph[MAXN];

void dfs(int x, int p){
	din[x] = piv++;
	for(auto &i : gph[x]) if(i != p) dfs(i, x);
	dout[x] = piv - 1;
}

int main(){
	freopen("snowcow.in", "r", stdin);
	freopen("snowcow.out", "w", stdout);
	scanf("%d %d",&n,&q);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=0; i<q; i++){
		int t; scanf("%d",&t);
		if(t == 1){
			int x, c; scanf("%d %d",&x,&c);
			insert(c, din[x], dout[x]);
		}
		else{
			int x; scanf("%d",&x);
			printf("%lld\n", seg.query(din[x], dout[x]));
		}
	}
}
