#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 500005;
const int MAXT = 1050000;
const int mod = 1e9 + 7;

struct seg{
	lint tree[MAXT];
	lint lazy[MAXT];
	void init(int s, int e, int p){
		if(s == e){
			tree[p] = s - 1;
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	void lazydown(int p){
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps+pe)/2;
		lazydown(p);
		return max(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg;

int n, q;
int main(){
	scanf("%d %d",&n,&q);
	seg.init(1, n, 1);
	int maxptr = 0;
	while(q--){
		int l, r, v;
		scanf("%d %d %d",&l,&r,&v);
		maxptr = max(maxptr, r);
		seg.add(l, r, 1, n, 1, v);
		printf("%lld\n", seg.query(1, maxptr, 1, n, 1));
	}
}

