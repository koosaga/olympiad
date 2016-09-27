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

struct pnt{
	int x, y, v, idx;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[1005];

struct evnt{
	int x, y, p1, p2;
	bool operator<(const evnt &e)const{
		return 1ll * x * e.y - 1ll * y * e.x > 0;
	}
};

struct seg{
	struct node{
		int l, r, m, s;
	}tree[2100];
	int lim;
	node merge(node &l, node &r){
		node ret;
		ret.l = l.l + (l.s == l.l ? r.l : 0);
		ret.r = r.r + (r.s == r.r ? l.r : 0);
		ret.m = max({l.m, r.m, l.r + r.l});
		ret.s = l.s + r.s;
		return ret;
	}
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=0; i<n; i++){
			tree[i+lim] = {0, 0, 0, 1};
		}
		for(int i=lim-1; i; i--){
			tree[i] = merge(tree[2*i], tree[2*i+1]);
		}
	}
	void set(int x, int v){
		x += lim;
		tree[x] = {v, v, v, 1};
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	int query(){ return tree[1].m; }
}seg;

int n, rev[1005];
vector<evnt> v;

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		string buf;
		cin >> a[i].x >> a[i].y >> buf;
		a[i].idx = i;
		a[i].v = (buf == "R");
	}
	sort(a, a+n);
	seg.init(n);
	for(int i=0; i<n; i++){
		rev[a[i].idx] = i;
		seg.set(i, a[i].v);
	}
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			v.push_back({a[j].x - a[i].x, a[j].y - a[i].y, a[i].idx, a[j].idx});
		}
	}
	sort(v.begin(), v.end());
	int r = 0;
	for(int i=0; i<v.size(); i++){
		int e = i;
		while(e+1 < v.size() && !(v[e] < v[e+1])) e++;
		for(int j=i; j<=e; j++){
			int i1 = rev[v[j].p1];
			int i2 = rev[v[j].p2];
			swap(a[i1], a[i2]);
			seg.set(i1, a[i1].v);
			seg.set(i2, a[i2].v);
			swap(rev[v[j].p1], rev[v[j].p2]);
		}
		r = max(r, seg.query());
		i = e;
	}
	cout << r;
}
