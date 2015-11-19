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

struct seg{
	int tree[270000], lazy[270000];
	void lazydown(int p){
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void init(int s, int e, int *a, int p){
		if(s == e){
			tree[p] = a[s];
			return;
		}
		int m = (s+e)/2;
		lazydown(p);
		init(s, m, a, 2*p);
		init(m+1, e, a, 2*p+1);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	int query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e9;
		if(s <= ps && pe <= e) return tree[p];
		lazydown(p);
		int pm = (ps + pe) / 2;
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
	void add(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			lazy[p]--;
			tree[p]--;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2*p);
		add(s, e, pm+1, pe, 2*p+1);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
}seg;

int n, m, c[100005];

struct tmp{
	int s, e;
}a[100005];

bool cmp(tmp a, tmp b){
	return a.e == b.e ? (a.s > b.s) : (a.e < b.e);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&c[i]);
	}
	seg.init(1, n, c, 1);
	for(int i=0; i<m; i++){
		scanf("%d %d",&a[i].s, &a[i].e);
	}
	sort(a, a+m, cmp);
	int cnt = 0;
	for(int i=0; i<m; i++){
		int t = seg.query(a[i].s, a[i].e, 1, n, 1);
		if(t > 0) cnt++, seg.add(a[i].s, a[i].e, 1, n, 1);
	}
	printf("%d",cnt);
}