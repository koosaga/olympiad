#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;
const int MAXT = 2000005;

struct strongly_connected{
	vector<vector<int>> gph;

	void init(int n){
		gph.resize(n);
	}

	void add_edge(int s, int e){
		gph[s].push_back(e);
	}

vector<int> val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for(auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	for(int i=0; i<n; i++) if (comp[i] < 0) dfs(i, g, f);
}

int piv;
	void get_scc(int n){
		scc(gph, [&](vector<int> &v){});
		for(int i=0; i<n; i++){
			comp[i] = ncomps - comp[i];
		}
		piv = ncomps; 
	}
}scc;

struct twosat{
	strongly_connected scc;
	int n;
	void init(int _n){ scc.init(2*_n); n = _n; }
	int NOT(int x){ return x >= n ? (x - n) : (x + n); }
	void add_edge(int x, int y){
		if((x >> 31) & 1) x = (~x) + n;
		if((y >> 31) & 1) y = (~y) + n;
		scc.add_edge(x, y), scc.add_edge(NOT(y), NOT(x));
	}
	bool satisfy(vector<int> &res){
		scc.get_scc(2*n);
		for(int i=0; i<n; i++){
			if(scc.comp[i] == scc.comp[NOT(i)]) return 0;
			if(scc.comp[i] < scc.comp[NOT(i)]) res[i] = 0;
			else res[i] = 1;
		}
		return 1;
	}
}twosat;

struct point{
	int x, y, idx;
}a[MAXN];

int n, vis[MAXN], cmp;
vector<int> gph[MAXN];

struct edg{
	int i1, i2, cmp;
};

vector<pi> ev_in[MAXN];
vector<pi> ev_out[MAXN];
vector<edg> cur_insec[MAXN];

int ds[MAXN];

struct node{
	int l, r;
}tree[MAXT]; 

int newnode(){ return cmp++; }
int root[MAXN];

void init(int s, int e, int p){
	if(s == e) return;
	tree[p].l = newnode();
	tree[p].r = newnode();
	int m = (s+e)/2;
	init(s, m, tree[p].l);
	init(m+1, e, tree[p].r);
	twosat.add_edge(p, tree[p].l);
	twosat.add_edge(p, tree[p].r);
}

void upd(int pos, int s, int e, int prv, int cur, int val){
	if(s == e){
		if(~val) twosat.add_edge(cur, val);
		return;
	}
	int m = (s+e)/2;
	if(pos <= m){
		tree[cur].l = newnode();
		tree[cur].r = tree[prv].r;
		upd(pos, s, m, tree[prv].l, tree[cur].l, val);
	}
	else{
		tree[cur].r = newnode();
		tree[cur].l = tree[prv].l;
		upd(pos, m+1, e, tree[prv].r, tree[cur].r, val);
	}
	twosat.add_edge(cur, tree[cur].l);
	twosat.add_edge(cur, tree[cur].r);
}

void query(int s, int e, int ps, int pe, int p, int v){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		twosat.add_edge(v, p);
		return;
	}
	int pm = (ps+pe)/2;
	query(s, e, ps, pm, tree[p].l, v);
	query(s, e, pm+1, pe, tree[p].r, v);
}

void Do(vector<edg> &vert, vector<edg> &hori){
	for(auto &i : vert){
		ev_in[a[i.i1].y].emplace_back(a[i.i1].x, i.cmp);
		ev_out[a[i.i2].y + 1].emplace_back(a[i.i1].x, -1);
	}
	for(auto &i : hori){
		cur_insec[a[i.i1].y].push_back(i);
	}
	root[0] = newnode();
	init(1, 100000, root[0]);
	for(int i=1; i<MAXN; i++){
		int prv = root[i - 1];
		for(auto &j : ev_out[i]){
			int nxt = newnode();
			upd(j.first, 1, 100000, prv, nxt, j.second);
			prv = nxt;
		}
		for(auto &j : ev_in[i]){
			int nxt = newnode();
			upd(j.first, 1, 100000, prv, nxt, j.second);
			prv = nxt;
		}
		root[i] = prv;
		for(auto &j : cur_insec[i]){
			int s = a[j.i1].x;
			int e = a[j.i2].x;
			query(s, e, 1, 100000, root[i], ~j.cmp);
		}
	}
}

vector<edg> edges;

void dfs(int x, int p, int q){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(i != p){
			edges.push_back({i, x, q});
			dfs(i, x, ~q);
			break;
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].idx = i;
	}
	if(n % 2 == 1){
		puts("NE");
		return 0;
	}
	sort(a, a + n, [&](const point &a, const point &b){
		return pi(a.x, a.y) < pi(b.x, b.y);
	});
	for(int i=1; i<n; i++){
		if(a[i-1].x == a[i].x){
			gph[a[i-1].idx].push_back(a[i].idx);
			gph[a[i].idx].push_back(a[i-1].idx);
		}
	}
	sort(a, a + n, [&](const point &a, const point &b){
		return pi(a.y, a.x) < pi(b.y, b.x);
	});
	for(int i=1; i<n; i++){
		if(a[i-1].y == a[i].y){
			gph[a[i-1].idx].push_back(a[i].idx);
			gph[a[i].idx].push_back(a[i-1].idx);
		}
	}
	sort(a, a + n, [&](const point &a, const point &b){
		return a.idx < b.idx;
	});
	twosat.init(2040000);
	for(int i=0; i<n; i++){
		if(vis[i]) continue;
		if(sz(gph[i]) == 0){
			puts("NE");
			return 0;
		}
		if(sz(gph[i]) == 1){
			int cur_edge = sz(edges);
			dfs(i, -1, cmp);
			int diff_edge = sz(edges) - cur_edge;
			if(diff_edge % 2){
				twosat.add_edge(~cmp, cmp);
			}
			cmp++;
		}
	}
	for(int i=0; i<n; i++){
		if(vis[i]) continue;
		if(sz(gph[i]) == 2){
			dfs(i, -1, cmp);
			cmp++;
		}
	}
	vector<edg> vert, hori;
	for(auto &i : edges){
		if(a[i.i1].x == a[i.i2].x) vert.push_back(i);
		else hori.push_back(i);
	}
	for(auto &i : vert) if(a[i.i1].y > a[i.i2].y) swap(i.i1, i.i2);
	for(auto &i : hori) if(a[i.i1].x > a[i.i2].x) swap(i.i1, i.i2);
	Do(vert, hori);
	vector<int> ans; ans.resize(2040000);
	if(!twosat.satisfy(ans)){
		puts("NE");
		return 0;
	}
	puts("DA");
	for(auto &i : edges){
		if(i.cmp < 0 && !ans[~i.cmp]) printf("%d %d\n", i.i1 + 1, i.i2 + 1);
		if(i.cmp >= 0 && ans[i.cmp]) printf("%d %d\n", i.i1 + 1, i.i2 + 1);
	}
}
