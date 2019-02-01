#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int inf = 2e9;

struct seg{
	struct node{
		lint max, add, l, r;
	}tree[1050000];
	void init(int s, int e, int p, int *h){
		if(s == e){
			tree[p] = {h[s], 0, -inf, inf};
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, h);
		init(m+1, e, 2*p+1, h);
		tree[p] = {max(tree[2*p].max, tree[2*p+1].max), 0, -inf, inf};
	}
	void push(int p){
		for(int i=2*p; i<2*p+2; i++){
			tree[i].add += tree[p].add;
			tree[i].max += tree[p].add;
			tree[i].l += tree[p].add;
			tree[i].r += tree[p].add;
			tree[i].l = max(tree[i].l, tree[p].l);
			tree[i].l = min(tree[i].l, tree[p].r);
			tree[i].r = max(tree[i].r, tree[p].l);
			tree[i].r = min(tree[i].r, tree[p].r);
			tree[i].max = max(tree[i].max, tree[p].l);
			tree[i].max = min(tree[i].max, tree[p].r);
		}
		tree[p] = {tree[p].max, 0, -inf, inf};
	}
	void add(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].add += v;
			tree[p].max += v;
			tree[p].l += v;
			tree[p].r += v;
			return;
		}
		int pm = (ps + pe) / 2;
		push(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p].max = max(tree[2*p].max, tree[2*p+1].max);
	}
	void set1(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].r = min(tree[p].r, v);
			tree[p].l = min(tree[p].l, v);
			tree[p].max = min(tree[p].max, v);
			return;
		}
		int pm = (ps + pe) / 2;
		push(p);
		set1(s, e, ps, pm, 2*p, v);
		set1(s, e, pm+1, pe, 2*p+1, v);
		tree[p].max = max(tree[2*p].max, tree[2*p+1].max);
	}
	void set2(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].r = max(tree[p].r, v);
			tree[p].l = max(tree[p].l, v);
			tree[p].max = max(tree[p].max, v);
			return;
		}
		int pm = (ps + pe) / 2;
		push(p);
		set2(s, e, ps, pm, 2*p, v);
		set2(s, e, pm+1, pe, 2*p+1, v);
		tree[p].max = max(tree[2*p].max, tree[2*p+1].max);
	}
	int query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return -1e9;
		if(s <= ps && pe <= e) return tree[p].max;
		int pm = (ps + pe) / 2;
		push(p);
		return max(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg;

int n, q, a[500005];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	seg.init(1, n, 1, a);
	while(q--){
		int t;
		scanf("%d",&t);
		if(t != 4){
			int l, r, v;
			scanf("%d %d %d",&l,&r,&v);
			if(t == 1) seg.add(l, r, 1, n, 1, v);
			if(t == 2) seg.set1(l, r, 1, n, 1, v);
			if(t == 3) seg.set2(l, r, 1, n, 1, v);
		}
		else{
			int l, r;
			scanf("%d %d",&l,&r);
			printf("%d\n", seg.query(l, r, 1, n, 1));
		}
	}
}
