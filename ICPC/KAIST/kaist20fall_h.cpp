#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int MAXT = 270000;

int n, q;

struct seg{
	struct node{
		lint sum, lazy;
	}tree[MAXT];
	void lazydown(int p, int ps, int pe){
		int pm = (ps+pe)/2;
		int len[2] = {pm - ps + 1, pe - pm};
		for(int i=2*p; i<2*p+2; i++){
			tree[i].sum += tree[p].lazy * len[i - 2*p];
			tree[i].lazy += tree[p].lazy;
		}
		tree[p].lazy = 0;
	}
	void add(int s, int e, int x, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].sum += x * (pe - ps + 1);
			tree[p].lazy += x;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p, ps, pe);
		add(s, e, x, ps, pm, 2*p);
		add(s, e, x, pm+1, pe, 2*p+1);
		tree[p].sum = tree[2*p].sum + tree[2*p+1].sum;
	}
	lint query(int s, int e, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p].sum;
		int pm = (ps+pe)/2;
		lazydown(p, ps, pe);
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
	int get_kth(lint k, int s = 1, int e = n, int p = 1){
		if(s == e) return s;
		lazydown(p, s, e);
		int m = (s+e)/2;
		if(k <= tree[2*p].sum) return get_kth(k, s, m, 2*p);
		return get_kth(k - tree[2*p].sum, m+1, e, 2*p+1);
	}
}seg;

vector<int> gph[MAXN];
int dep[MAXN], par[17][MAXN], din[MAXN], dout[MAXN], rev[MAXN], sz[MAXN], piv;
int chn[MAXN];

void dfs(int x){
	sz[x] = 1;
	for(auto &i : gph[x]){
		gph[i].erase(find(all(gph[i]), x));
		dep[i] = dep[x] + 1;
		par[0][i] = x;
		dfs(i);
		sz[x] += sz[i];
	}
}

void hld(int x){
	if(x == 1){
		chn[1] = 1;
	}
	din[x] = ++piv;
	rev[din[x]] = x;
	sort(all(gph[x]), [&](const int &a, const int &b){
		return sz[a] > sz[b];
	});
	if(sz(gph[x]) > 0){
		chn[gph[x][0]] = chn[x];
		hld(gph[x][0]);
		for(int i = 1; i < sz(gph[x]); i++){
			chn[gph[x][i]] = gph[x][i];
			hld(gph[x][i]);
		}
	}
	dout[x] = piv;
}

int lca(int x, int y){
	if(dep[x] < dep[y]) swap(x, y);
	int dx = dep[x] - dep[y];
	for(int i=0; dx; i++){
		if(dx & 1) x = par[i][x];
		dx >>= 1;
	}
	for(int i=16; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int x, y; scanf("%d %d",&x,&y);
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	dfs(1);
	hld(1);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	scanf("%d",&q);
	while(q--){
		int t, u, v;
		scanf("%d",&t);
		if(t == 1){
			scanf("%d",&u);
			seg.add(din[u], dout[u], 1);
		}
		else{
			scanf("%d %d",&u,&v);
			int l = lca(u, v);
			while(chn[u] != chn[l]){
				seg.add(din[chn[u]], din[u], 1);
				u = par[0][chn[u]];
			}
			while(chn[v] != chn[l]){
				seg.add(din[chn[v]], din[v], 1);
				v = par[0][chn[v]];
			}
			if(din[u] > din[v]) swap(u, v);
			seg.add(din[u], din[v], 1);
		}
		auto getSum = [&](int v){ return seg.query(din[v], dout[v]); };
		lint thres = getSum(1);
		int pos = rev[seg.get_kth((thres + 1) / 2)];
		for(int i = 16; i >= 0; i--){
			if(par[i][pos] && getSum(par[i][pos]) <= thres / 2){
				pos = par[i][pos];
			}
		}
		if(getSum(pos) <= thres / 2) pos = par[0][pos];
		printf("%d\n", pos);
	}
}

