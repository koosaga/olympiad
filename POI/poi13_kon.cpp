#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int N, K;

struct bit{
	int tree[300005];
	void add(int x, int v){
		x++;
		while(x <= N){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		x++;
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

struct seg{
	pi tree[1050000];
	int lazy[1050000];
	void init(int s, int e, int p, int *a){
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
		tree[2*p].first += lazy[p];
		tree[2*p+1].first += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].first+=v;
			lazy[p]+=v;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
}seg;

void inicjuj(int n, int k, int *D)
{
	N = n, K = k;
	seg.init(0, n-1, 1, D);
	while(seg.tree[1].first >= K){
		bit.add(seg.tree[1].second, 1);
		seg.add(seg.tree[1].second, seg.tree[1].second, 0, N-1, 1, -1e9);
	}
}

void podlej(int a, int b)
{
	seg.add(a, b, 0, N-1, 1, 1);
	while(seg.tree[1].first >= K){
		bit.add(seg.tree[1].second, 1);
		seg.add(seg.tree[1].second, seg.tree[1].second, 0, N-1, 1, -1e9);
	}
}

int dojrzale(int a, int b)
{
	return bit.query(b) - bit.query(a-1);
}
