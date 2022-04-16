#include "breakthru.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 10005;
const int MAXT = 66666;

struct ans{
	lint val;
	int cx, cy;
	ans(){ val = cx = cy = 0;  }
	ans(lint cval){
		val = cval;
		cx = cy = 0;
	}
	bool operator<(const ans &a)const{
		return val < a.val;
	}
};

struct node{
	ans val;
	lint lazy1, lazy2;
	ans minim;
	node(){
		val = ans();
		lazy1 = lazy2 = 0;
		minim = ans(1e18);
	}
	void add(lint x, lint y){
		val.cy += x;
		val.val += y;
		lazy1 += x;
		lazy2 += y;
		minim.cy += x;
		minim.val += y;
	}
};

int n, m;
pi a[MAXN];

struct seg{
	node tree[MAXT];
	void clear(){ fill(tree, tree + MAXT, node()); }
	void lazydown(int p){
		for(int j=2*p; j<2*p+2; j++){
			tree[j].add(tree[p].lazy1, tree[p].lazy2);
			tree[j].minim = min(tree[j].minim, tree[p].minim);
			tree[j].val = min(tree[j].val, tree[p].minim);
		}
		tree[p].lazy1 = tree[p].lazy2 = 0;
		tree[p].minim = ans(1e18);
	}
	void add(int s, int e, int x, int ps = 0, int pe = m - 1, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].add(1, x);
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, x, ps, pm, 2*p);
		add(s, e, x, pm+1, pe, 2*p+1);
		tree[p].val = min(tree[2*p].val, tree[2*p+1].val);
	}
	void apply_min(ans p){
		tree[1].val = min(tree[1].val, p);
		tree[1].minim = min(tree[1].minim, p);
	}
}seg;

pi haja(int A, int B){
	seg.clear();
	for(int i=0; i<n; i++){
		seg.add(a[i].first, a[i].second - 1, B);
		ans gm = seg.tree[1].val; 
		gm.val += A;
		gm.cx += 1;
		seg.apply_min(gm);
	}
	auto val = seg.tree[1].val;
	return pi(val.cx, val.cy);
}

vector<pi> cvxh;

void solve(pi x, pi y){
	auto ccw = [&](pi a, pi b, pi c){
		int dx1 = b.first - a.first;
		int dy1 = b.second - a.second;
		int dx2 = c.first - a.first;
		int dy2 = c.second - a.second;
		return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
	};
	auto qr = haja(y.second - x.second, x.first - y.first);
	if(ccw(qr, x, y) > 0){
		solve(x, qr);
		cvxh.push_back(qr);
		solve(qr, y);
	}
}

void init(int N, int M, std::vector<int> Y1, std::vector<int> Y2){
	vector<int> crd = {0, M};
	for(int i=0; i<N; i++){
		crd.push_back(Y1[i]);
		crd.push_back(Y2[i] + 1);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for(int i=0; i<N; i++){
		a[i].first = lower_bound(all(crd), Y1[i]) - crd.begin();
		a[i].second = lower_bound(all(crd), Y2[i] + 1) - crd.begin();
	}
	n = N;
	m = sz(crd) - 1;
	solve(pi(n + 1, 0), pi(0, n + 1));
}

long long minimize(int A, int B){
	auto f = [&](int x){
		return 1ll * cvxh[x].first * A + 1ll * cvxh[x].second * B;
	};
	int s = 0, e = sz(cvxh) - 1;
	while(s != e){
		int m = (s+e)/2;
		if(f(m) < f(m + 1)) e = m;
		else s = m + 1;
	}
	return f(s);
}
