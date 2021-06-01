#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 250005;
const int MAXT = 530005;

int n, par[MAXN], pae[MAXN], sz[MAXN], chn[MAXN];
lint cost[MAXN], cap[MAXN];
int din[MAXN], dout[MAXN], rev[MAXN], piv;
pi a[MAXN], b[MAXN];
vector<pi> gph[MAXN];

struct seg{
	pi tree[MAXT];
	lint lazy[MAXT];
	void init(int s, int e, int p, lint* a){
		if(s == e){
			tree[p] = pi(a[s], s);
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, a);
		init(m+1, e, 2*p+1, a);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	void lazydown(int p){
		for(int i = 2*p; i<2*p+2; i++){
			lazy[i] += lazy[p];
			tree[i].first += lazy[p];
		}
		lazy[p] = 0;
	}

	void add(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].first += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
}seg, seg2;

void dfs(int x, int p){
	sz[x] = 1;
	b[x] = a[x];
	for(auto &[w, v] : gph[x]){
		gph[v].erase(find(all(gph[v]), pi(w, x)));
		par[v] = x;
		pae[v] = w;
		dfs(v, x);
		b[x].first += b[v].first;
		b[x].second += b[v].second;
		sz[x] += sz[v];
	}
}

void hld(int x, int p){
	din[x] = ++piv;
	rev[din[x]] = x;
	sort(all(gph[x]), [&](const pi &a, const pi &b){
		return sz[a.second] > sz[b.second];
	});
	if(sz(gph[x])){
		chn[gph[x][0].second] = chn[x];
		hld(gph[x][0].second, x);
	}
	for(int i = 1; i < sz(gph[x]); i++){
		chn[gph[x][i].second] = gph[x][i].second;
		hld(gph[x][i].second, x);
	}
	dout[x] = piv;
}

void dfs2(int x, int p){
	for(auto &[w, v] : gph[x]){
		if(v != p){
			cost[din[v]] = cost[din[x]] + (cap[din[v]] > 0 ? pae[v] : -pae[v]);
			dfs2(v, x);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i = 1; i < n; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	for(int i = 1; i <= n; i++){
		scanf("%lld %lld",&a[i].first,&a[i].second);
	}
	dfs(1, 0);
	hld(1, 0);
	int slack = b[1].first - b[1].second;
	lint ret = 0;
	for(int i = 2; i <= n; i++){
		ret += abs(b[i].first - b[i].second) * pae[i];
		cap[din[i]] = max(b[i].first - b[i].second, 0ll);
	}
	dfs2(1, 0);
	for(int i = 1; i <= n; i++){
		if(!a[i].first) cost[din[i]] = -1e18;
		if(!cap[i]) cap[i] = 1e9;
		cap[i] = -cap[i];
	}
	seg.init(1, n, 1, cost);
	seg2.init(1, n, 1, cap);
	while(slack--){
		pi foo = seg.tree[1];
		int v = rev[foo.second];
		a[v].first--;
		if(!a[v].first){
			seg.add(din[v], din[v], 1, n, 1, -1e18);
		}
		ret -= foo.first;
		for(int j = v; j; j = par[chn[j]]){
			int st = din[chn[j]], ed = din[j];
			seg2.add(st, ed, 1, n, 1, 1);
		}
		while(seg2.tree[1].first == 0){
			int j = seg2.tree[1].second;
			int v = rev[j];
			seg.add(din[v], dout[v], 1, n, 1, -2 * pae[v]);
			seg2.add(j, j, 1, n, 1, -1e9);
		}
	}
	cout << ret << endl;
}

