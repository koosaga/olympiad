#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

struct seg{
	struct node{
		lint l, r, v, s;
	}tree[530000];
	int lim;
	node merge(node &l, node &r){
		node ret;
		ret.s = l.s + r.s;
		ret.l = max(l.l, l.s + r.l);
		ret.r = max(r.r, r.s + l.r);
		ret.v = max({l.v, r.v, l.r + r.l});
		return ret;
	}
	void init(int n, int k){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<=n; i++){
			tree[i + lim] = {0, 0, 0, -k};
		}
		for(int i=lim; i; i--) tree[i] = merge(tree[2*i], tree[2*i+1]);
	}
	void update(int x, int v){
		x += lim;
		tree[x].s += v;
		tree[x].l = tree[x].r = tree[x].v = max(tree[x].s, 0ll);
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	lint query(){ return tree[1].v; }
}seg;

int n, q, k, d;

int main(){
	scanf("%d %d %d %d",&n,&q,&k,&d);
	seg.init(n, k);
	for(int i=0; i<q; i++){
		int x, v;
		scanf("%d %d",&x,&v);
		seg.update(x, v);
		puts(seg.query() <= 1ll * k * d ? "TAK" : "NIE");
	}
}

