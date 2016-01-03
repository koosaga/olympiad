#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct seg1{
	lint tree[530000], lazy[530000];
	void init(int s, int e, int p, int *x){
		if(s == e){
			tree[p] = x[s];
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, x);
		init(m+1, e, 2*p+1, x);
		tree[p] = min(tree[2*p], tree[2*p+1]);
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
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e18;
		if(s <= ps && pe <= e) return tree[p];
		lazydown(p);
		int pm = (ps + pe) / 2;
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg1;

struct seg2{
	lint tree[530000], lazy[530000];
	void init(int s, int e, int p, int *x){
		if(s == e){
			tree[p] = x[s];
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, x);
		init(m+1, e, 2*p+1, x);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	void lazydown(int p, int ps, int pe){
		int pm = (ps + pe) / 2;
		tree[2*p] += lazy[p] * (pm - ps + 1);
		tree[2*p+1] += lazy[p] * (pe - pm);
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += 1ll * (pe - ps + 1) * v;
			lazy[p] += v;
			return;
		}
		lazydown(p, ps, pe);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p];
		lazydown(p, ps, pe);
		int pm = (ps + pe) / 2;
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
}seg2;

int n, q, a[200005];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	seg1.init(1, n, 1, a);
	seg2.init(1, n, 1, a);
	for(int i=0; i<q; i++){
		char buf[5];
		scanf("%s",buf);
		if(*buf == 'M'){
			int s, e;
			scanf("%d %d",&s,&e);
			printf("%lld\n",seg1.query(s, e, 1, n, 1));
		}
		if(*buf == 'S'){
			int s, e;
			scanf("%d %d",&s,&e);
			printf("%lld\n",seg2.query(s, e, 1, n, 1));
		}
		if(*buf == 'P'){
			int s, e, x;
			scanf("%d %d %d",&s,&e,&x);
			seg1.add(s, e, 1, n, 1, x);
			seg2.add(s, e, 1, n, 1, x);
		}
	}
}