#include "candies.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 200005;
const int MAXT = 530000;

pi merge(pi a, pi b){
	return pi(min(a.first, b.first), max(a.second, b.second));
}

struct seg{
	pi tree[MAXT];
	lint lazy[MAXT];
	void lazydown(int p){
		for(int i = 2*p; i < 2*p+2; i++){
			tree[i].first += lazy[p];
			tree[i].second += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			lazy[p] += v;
			tree[p].first += v;
			tree[p].second += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
	pi query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return pi(1e18, -1e18);
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps+pe)/2;
		lazydown(p);
		return merge(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
	int first_fail(int s, int e, int p, int c, pi v){
		if(s == e) return s;
		int m = (s+e)/2;
		lazydown(p);
		auto mrg = merge(v, tree[2*p+1]);
		if(mrg.second - mrg.first > c) return first_fail(m+1, e, 2*p+1, c, v);
		return first_fail(s, m, 2*p, c, mrg);
	}
}seg;

vector<pi> upd[MAXN];

std::vector<int> distribute_candies(std::vector<int> c, std::vector<int> l,
                                    std::vector<int> r, std::vector<int> v) {

    int n = c.size();
    int q = l.size();
    for(int i = 0; i < q; i++){
    	upd[l[i]].emplace_back(v[i], i);
    	upd[r[i]+1].emplace_back(-v[i], i);
	}
    std::vector<int> s(n);
    lint T = 0;
	for(int i = 0; i < n; i++){
		for(auto &[v, x] : upd[i]){
			seg.add(x+1, q, 0, q, 1, v);
			T += v;
		}
		if(seg.tree[1].second - seg.tree[1].first <= c[i]){
			s[i] = T - seg.tree[1].first;
			continue;
		}
		int j = seg.first_fail(0, q, 1, c[i], pi(T, T));
		pi X = seg.query(j, q, 0, q, 1);
		pi Y = seg.query(j + 1, q, 0, q, 1);
		if(X.second != Y.second){
			s[i] = T - Y.first;
		}
		else{
			s[i] = c[i] - (Y.second - T);
		}
	}
    return s;
}
