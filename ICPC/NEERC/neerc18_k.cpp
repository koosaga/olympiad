#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 1000005;
const int MAXT = 2100000;
int q;

char buf[100];

struct bit{
	lint tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	lint query(int x){
		lint ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

struct seg{
	lint tree[MAXT], lazy[MAXT];
	void init(int s, int e, int p){
		if(s == e){
			tree[p] = s;
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2*p);
		init(m + 1, e, 2* p + 1);
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
		int pm = (ps + pe) / 2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return -1e18;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps + pe) / 2;
		lazydown(p);
		return max(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg;

int a[MAXN], T[MAXN], D[MAXN];

int main(){
	scanf("%d",&q);
	seg.init(1, 1000000, 1);
	for(int i=1; i<=q; i++){
		scanf("%s", buf);
		if(*buf == '?'){
			int t; scanf("%d",&t);
			printf("%lld\n", bit.query(t) + seg.query(1, t, 1, 1000000, 1) - t);
		}
		if(*buf == '+'){
			scanf("%d %d",&T[i],&D[i]);
			bit.add(T[i], D[i]);
			seg.add(T[i] + 1, 1000000, 1, 1000000, 1, -D[i]); 
		}
		if(*buf == '-'){
			int prv; scanf("%d",&prv);
			bit.add(T[prv], -D[prv]);
			seg.add(T[prv] + 1, 1000000, 1, 1000000, 1, D[prv]);
		}
	}
}