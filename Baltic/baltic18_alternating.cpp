#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 250005;
const int MAXT = 530000;
#define sz(v) ((int)((v).size()))

struct bit{
	pi tree[MAXT];
	void init(){
		fill(tree, tree + MAXT, pi(0, 0));
	}
	void upd(int x, pi v){
		while(x < MAXT){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	pi query(int x){
		pi ret(0, 0);
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
}bit;

struct seg{
	int tree[MAXT], lazy[MAXT];
	void init(){
		memset(tree, 0, sizeof(tree));
		memset(lazy, 0, sizeof(lazy));
	}
	void lazydown(int p){
		for(int i=0; i<2; i++){
			tree[2*p+i] += lazy[p];
			lazy[2*p+i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
}seg[2];

struct segment{
	int s, e, idx;
	int len;
};

int n, m, nxt[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	vector<segment> a(m);
	vector<segment> dom;
	for(int i=0; i<m; i++){
		scanf("%d %d",&a[i].s,&a[i].e);
		a[i].idx = i;
		a[i].len = a[i].e - a[i].s + 1;
		if(a[i].len <= 0) a[i].len += n;
	}
	sort(a.begin(), a.end(), [&](const segment &a, const segment &b){
		return a.len < b.len;
	});
	memset(nxt, -1, sizeof(nxt));
	bit.init();
	seg[0].init();
	seg[1].init();
	for(int i=m-1; i>=0; i--){
		int domidx = -1;
		int st = a[i].s, ed = a[i].e;
		if(st > ed) ed += n;
		auto qr1 = bit.query(st);
		if(qr1.first >= ed){
			domidx = qr1.second;
		}
		if(domidx == -1 && a[i].s <= a[i].e){
			auto qr2 = bit.query(st + n);
			if(qr2.first >= ed + n){
				domidx = qr2.second;
			}
		}
		nxt[a[i].idx] = domidx;
		if(nxt[a[i].idx] == -1){
			dom.push_back(a[i]);
			bit.upd(st, pi(ed, a[i].idx));
			if(a[i].s <= a[i].e) bit.upd(st + n, pi(ed + n, a[i].idx));
		}
	}
	sort(dom.begin(), dom.end(), [&](const segment &a, const segment &b){
		return a.s < b.s;
	});
	vector<int> col(m);
	vector<int> gph[MAXN];
	for(int i=0; i<sz(dom); i++) col[dom[i].idx] = 1 + i % 2;
	for(int i=0; i<m; i++){
		if(nxt[i] != -1){
			col[i] = 3 - col[nxt[i]];
			gph[nxt[i]].push_back(i);
		}
	}
	sort(a.begin(), a.end(), [&](const segment &a, const segment &b){
		return a.idx < b.idx;
	});
	auto fetch = [&](int i, int v){
		if(a[i].s <= a[i].e){
			seg[col[i] - 1].add(a[i].s, a[i].e, 1, n, 1, v);
		}
		else{
			seg[col[i] - 1].add(a[i].s, n, 1, n, 1, v);
			seg[col[i] - 1].add(1, a[i].e, 1, n, 1, v);
		}
	};
	for(int i=0; i<m; i++){
		fetch(i, +1);
	}
	if(seg[0].tree[1] > 0 && seg[1].tree[1] > 0){
		for(auto &i : col) printf("%d\n", i - 1);
		return 0;
	}
	if(sz(dom) % 2 == 0 || sz(dom) <= 1){
		puts("-1");
		return 0;
	}
	for(int i=0; i<sz(dom); i++){
		fetch(dom[i].idx, -1);
		col[dom[i].idx] = 3 - col[dom[i].idx];
		fetch(dom[i].idx, +1);
		for(auto &j : gph[dom[i].idx]){
			fetch(j, -1);
			col[j] = 3 - col[j];
			fetch(j, 1);
		}
		if(seg[0].tree[1] > 0 && seg[1].tree[1] > 0){
			for(auto &i : col) printf("%d\n", i - 1);
			return 0;
		}
	}
	puts("-1");
}
