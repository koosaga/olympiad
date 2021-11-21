#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int MAXT = 270000;

struct event{
	int type;
	int x, y; // (vertex, value) or (start, end)
	int idx;
};

vector<event> events[MAXN];
vector<int> gph[MAXN];

int sz[MAXN], dep[MAXN], par[20][MAXN];
int din[MAXN], chn[MAXN], piv;

void dfs(int x){
	sz[x] = 1;
	for(auto &y : gph[x]){
		gph[y].erase(find(all(gph[y]), x));
		dep[y] = dep[x] + 1;
		par[0][y] = x;
		dfs(y);
		sz[x] += sz[y];
	}
}

void hld(int x){
	din[x] = piv++;
	if(sz(gph[x])){
		chn[gph[x][0]] = chn[x];
		hld(gph[x][0]);
	}
	for(int i = 1; i < sz(gph[x]); i++){
		int y = gph[x][i];
		chn[y] = y;
		hld(y);
	}
}

struct node{
	int dist, l, r, opt;
	node(): dist(0), l(1e9), r(1e9), opt(1e9) {}
	node(int x): dist(1), l(x ? 0 : 1e9), r(x ? 0 : 1e9), opt(1e9) {}
	node operator+(const node &n){
		node ret;
		ret.dist = dist + n.dist;
		ret.l = min(l, dist + n.l);
		ret.r = min(n.r, n.dist + r);
		ret.opt = min({opt, n.opt, r + n.l + 1});
		return ret;
	}
};

struct seg{
	node tree[MAXT];
	int lim;
	void init(int n){
		fill(tree, tree + MAXT, node());
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = node(v);
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	node query(int s, int e){
		s += lim;
		e += lim;
		node L, R;
		while(s < e){
			if(s%2 == 1) L = L + tree[s++];
			if(e%2 == 0) R = tree[e--] + R;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) L = L + tree[s];
		return L + R;
	}
}seg;

void init(int n){
	seg.init(n);
	for(int i = 0; i < n; i++) seg.upd(i, 0);
}

void upd(int x, int v){
	seg.upd(din[x], v);
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i = 0; dx; i++){
		if(dx & 1){
			e = par[i][e];
		}
		dx >>= 1;
	}
	for(int i = 19; i >= 0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

node queryL(int s, int e){
	return seg.query(s, e);
}

node query(int s, int e){
	int l = lca(s, e);
	vector<node> v;
	while(chn[s] != chn[l]){
		v.push_back(queryL(din[chn[s]], din[s]));
		s = par[0][chn[s]];
	}
	v.push_back(queryL(din[l], din[s]));
	vector<node> w;
	while(chn[e] != chn[l]){
		w.push_back(queryL(din[chn[e]], din[e]));
		e = par[0][chn[e]];
	}
	if(din[l] < din[e]){
		w.push_back(queryL(din[l] + 1, din[e]));
	}
	reverse(all(w));
	for(auto &i : v) swap(i.l, i.r);
	for(auto &i : w) v.push_back(i);
	for(int i = 1; i < sz(v); i++) v[0] = v[0] + v[i];
	return v[0];
}

int ret[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q; cin >> n >> q;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
		events[a[i]].push_back({0, i, 1, -1});
	}
	for(int i = 0; i < n-1; i++){
		int s, e; cin >> s >> e;
		s--; e--;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(0);
	for(int i = 0; i < n; i++){
		sort(all(gph[i]), [&](int x, int y){ return sz[x] > sz[y]; });
	}
	for(int i = 1; i < 20; i++){
		for(int j = 0; j < n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	hld(0);
	string buf;
	int cnt = 0;
	for(int i = 0; i < q; i++){
		cin >> buf;
		if(buf == "Q"){
			int u, v, c;
			cin >> u >> v >> c;
			u--; v--;
			events[c].push_back({1, u, v, cnt++});
		}
		else{
			int x, v; cin >> x >> v;
			x--;
			events[a[x]].push_back({0, x, 0, -1});
			a[x] = v;
			events[a[x]].push_back({0, x, 1, -1});
		}
	}
	for(int i = 0; i < n; i++){
		events[a[i]].push_back({0, i, 0, -1});
	}
	init(n);
	for(int i = 1; i <= n; i++){
		for(auto &x : events[i]){
			if(x.type == 0){
				upd(x.x, x.y);
			}
			else{
				ret[x.idx] = query(x.x, x.y).opt;
				if(ret[x.idx] > n) ret[x.idx] = -1;
			}
		}
	}
	for(int i = 0; i < cnt; i++) printf("%d\n", ret[i]);
}
