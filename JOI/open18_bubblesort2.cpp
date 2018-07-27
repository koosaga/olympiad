#include "bubblesort2.h"
#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 500005;

pi a[MAXN];
int p[2 * MAXN];
int chk[2 * MAXN];

struct seg{
	int tree[2100000], lazy[2100000];
	void init(){
		fill(tree, tree + 2100000, -1e9);
	}
	void lazydown(int p){
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
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
	void upd(int pos, int s, int e, int p, int v){
		if(s == e){
			tree[p] = v;
			return;
		}
		int m = (s+e)/2;
		lazydown(p);
		if(pos <= m) upd(pos, s, m, 2*p, v);
		else upd(pos, m+1, e, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	int query(int pos, int s, int e, int p){
		if(s == e) return tree[p];
		int m = (s+e)/2;
		lazydown(p);
		if(pos <= m) return query(pos, s, m, 2*p);
		else return query(pos, m+1, e, 2*p+1);
	}
}seg;

struct bit{
	int tree[2 * MAXN];
	void add(int x, int v){
		while(x < 2 * MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

std::vector<int> countScans(std::vector<int> A,std::vector<int> X,std::vector<int> V){
	int n=A.size();
	int Q=X.size();
	std::vector<int> answer(Q);	
	for(int i=0; i<n; i++) a[i] = pi(A[i], i);
	vector<pi> v;
	for(int i=0; i<n; i++) v.push_back(a[i]);
	for(int i=0; i<Q; i++) v.push_back(pi(V[i], X[i]));
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	auto getpos = [&](pi x){
		return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
	};
	seg.init();
	for(int i=0; i<n; i++){
		int pos = getpos(a[i]);
		p[pos] = i;
		chk[pos] = 1;
		bit.add(pos, 1);
	}
	for(int i=1; i<=v.size(); i++){
		if(chk[i]) p[i] -= bit.query(i) - 1;
		else p[i] = -1e9;
		seg.upd(i, 1, v.size(), 1, p[i]);
	}
	for(int i=0; i<Q; i++){
		int curpos = getpos(a[X[i]]);
		a[X[i]].first = V[i];
		int nxtpos = getpos(a[X[i]]);
		if(curpos <= nxtpos){
			int val = seg.query(curpos, 1, v.size(), 1) + bit.query(curpos) - 1;
			bit.add(curpos, -1);
			seg.add(curpos + 1, nxtpos, 1, v.size(), 1, 1);
			bit.add(nxtpos, 1);
			seg.upd(curpos, 1, v.size(), 1, -1e9);
			seg.upd(nxtpos, 1, v.size(), 1, val - bit.query(nxtpos) + 1);
		}
		else{
			int val = seg.query(curpos, 1, v.size(), 1) + bit.query(curpos) - 1;
			bit.add(curpos, -1);
			seg.add(nxtpos + 1, curpos, 1, v.size(), 1, -1);
			bit.add(nxtpos, 1);
			seg.upd(curpos, 1, v.size(), 1, -1e9);
			seg.upd(nxtpos, 1, v.size(), 1, val - bit.query(nxtpos) + 1);
		}
		int ans = max(seg.tree[1], 0);
		answer[i] = ans;
	}
	return answer;
}
