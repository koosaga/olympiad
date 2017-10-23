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
	int tree[132000], lazy[132000];
	void init(int s, int e, int x){
		if(s == e){
			tree[x] = 1e9;
			lazy[x] = 1e9;
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*x);
		init(m+1, e, 2*x+1);
		tree[x] = 1e9;
		lazy[x] = 1e9;
	}
	void push(int x){
		tree[2*x] = min(tree[2*x], lazy[x]);
		tree[2*x+1] = min(tree[2*x+1], lazy[x]);
		lazy[2*x] = min(lazy[2*x], lazy[x]);
		lazy[2*x+1] = min(lazy[2*x+1], lazy[x]);
		lazy[x] = 1e9;
	}
	int query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e9;
		if(s <= ps && pe <= e) return tree[p];
		push(p);
		int pm = (ps + pe) / 2;
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
	void update(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] = min(tree[p], v);
			lazy[p] = min(lazy[p], v);
			return;
		}
		push(p);
		int pm = (ps + pe) / 2;
		update(s, e, ps, pm, 2*p, v);
		update(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
}seg;

int m, n;

int main(){
	cin >> m >> n;
	seg.init(1, m, 1);
	seg.update(1, 1, 1, m, 1, 0);
	for(int i=1; i<=n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		int val = seg.query(s, e, 1, m, 1) + 1;
		seg.update(s, e, 1, m, 1, val);
	}
	cout << seg.query(m, m, 1, m, 1);
}