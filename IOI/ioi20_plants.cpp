#include "plants.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define rank fuck
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 200005;
const int MAXT = 2100005;
 
int n, rank[MAXN];
lint DL[18][MAXN], DR[18][MAXN];
int L[18][MAXN], R[18][MAXN];
vector<int> lev[MAXN];
 
struct node{
	int minv;
	int lidx, ridx;
	node(){
		minv = 1e9;
	}
	node(int x, int v){
		lidx = ridx = x;
		minv = v;
	}
	node operator+(const node &n)const{
		node x = *this;
		node y = n;
		if(x.minv < y.minv) return x;
		if(x.minv > y.minv) return y;
		x.lidx = min(x.lidx, y.lidx);
		x.ridx = max(x.ridx, y.ridx);
		return x;
	}
};
 
struct seg{
	node tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= 3 * n; lim <<= 1);
		for(int i=0; i<3*n; i++) tree[i + lim] = node(i-n, 1e9);
		for(int i=lim-1; i; i--) tree[i] = tree[2*i] + tree[2*i+1];
	}
	void upd(int x, int v){
		node val(x, v);
		x += n + lim;
		tree[x] = val;
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	node query(int s, int e){
		s += lim + n;
		e += lim + n;
		node ret;
		while(s < e){
			if(s%2 == 1) ret = ret + tree[s++];
			if(e%2 == 0) ret = ret + tree[e--];
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = ret + tree[s];
		return ret;
	}
}seg;
 
struct sex{
	int tree[530005], lazy[530005];
	void init(int s, int e, vector<int> &v, int p){
		if(s == e){
			tree[p] = v[s];
			return;
		}
		int m = (s+e)/2;
		init(s, m, v, 2*p);
		init(m+1, e, v, 2*p+1);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	void lazydown(int p){
		for(int i=2*p; i<2*p+2; i++){
			tree[i] += lazy[p];
			lazy[i] += lazy[p];
		}
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
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	int query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e9;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps+pe)/2;
		lazydown(p);
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
	int find_first(int s, int e, int p){
		if(tree[1] > 0) return 1e9;
		if(s == e) return s;
		lazydown(p);
		int m = (s+e)/2;
		if(!tree[2*p]) return find_first(s, m, 2*p);
		return find_first(m+1, e, 2*p+1);
	}
}sex;
 
void init(int k, std::vector<int> r) {
	n = sz(r);
	int layer = 0;
	set<int> unused;
	for(int i=0; i<n; i++) unused.insert(i);
	sex.init(0, n-1, r, 1);
	auto QUERY = [&](int st, int ed){
		int ret = 1e9;
		if(st < n) ret = min(ret, sex.query(st, min(ed, n - 1), 0, n - 1, 1));
		if(ed >= n) ret = min(ret, sex.query(max(st - n, 0), ed - n, 0, n - 1, 1));
		return ret;
	};
	auto cond = [&](int j){
		if(QUERY(j, j)) return false;
		return QUERY(j + n - (k - 1), j + n - 1) > 0;
	};
	auto ADD = [&](int st, int ed, int x){
		if(st < n) sex.add(st, min(ed, n - 1), 0, n - 1, 1, x);
		if(ed >= n) sex.add(max(st - n, 0), ed - n, 0, n - 1, 1, x);
	};
	auto FIND_FIRST = [&](int s, int k){
		ADD(0, s - 1, 1);
		int Q = sex.find_first(0, n - 1, 1);
		ADD(0, s - 1, -1);
		int R = sex.find_first(0, n - 1, 1);
		if(Q <= s + k - 1) return Q;
		if(R < n && (R - s + n) % n < k) return R;
		return -1;
	};
	vector<int> cur;
	for(int i=0; i<n; i++){
		if(cond(i)) cur.push_back(i);
	}
	while(sz(unused)){
		vector<int> nxt;
		layer++;
		for(auto &j : cur){
			if(unused.find(j) == unused.end()) continue;
			unused.erase(j);
			rank[j] = layer;
			ADD(j, j, k-1);
			ADD(j-k+1+n, j-1+n, -1);
			int p1 = (j - k + 1 + n) % n;
			int p2 = (j + 1) % n;
			int pos1 = FIND_FIRST(p1, k - 1);
			int pos2 = FIND_FIRST(p2, k - 1);
			if(~pos1 && cond(pos1)) nxt.push_back(pos1);
			if(~pos2 && cond(pos2)) nxt.push_back(pos2);
		}
		cur = nxt;
	}
	for(int i=0; i<n; i++){
		lev[rank[i]].push_back(i);
	}
	seg.init(n);
	for(int i=layer; i; i--){
		for(auto &j : lev[i]){
			L[0][j] = j;
			auto qr = seg.query(j-k+1, j-1);
			if(qr.minv > 1e8) continue;
			if(qr.lidx < j) L[0][j] = (qr.lidx + n) % n;
			DL[0][j] = (j - L[0][j] + n) % n;
		}
		for(auto &j : lev[i]){
			R[0][j] = j;
			auto qr = seg.query(j+1, j+k-1);
			if(qr.minv > 1e8) continue;
			if(qr.ridx > j) R[0][j] = (qr.ridx + n) % n;
			DR[0][j] = (R[0][j] - j + n) % n;
		}
		for(auto &j : lev[i]){
			seg.upd(j - n, i);
			seg.upd(j    , i);
			seg.upd(j + n, i);
		}
	}
	for(int i=1; i<18; i++){
		for(int j=0; j<n; j++){
			L[i][j] = L[i-1][L[i-1][j]];
			R[i][j] = R[i-1][R[i-1][j]];
			DL[i][j] = DL[i-1][j] + DL[i-1][L[i-1][j]];
			DR[i][j] = DR[i-1][j] + DR[i-1][R[i-1][j]];
		}
	}
}
 
int compare_plants(int x, int y) {
	if(rank[x] == rank[y]) return 0;
	if(rank[x] > rank[y]) return -compare_plants(y, x);
	lint st = x, ed = x;
	{
		lint dist = 0;
		int p = x;
		for(int i=17; i>=0; i--){
			if(rank[L[i][p]] <= rank[y]){
				dist += DL[i][p];
				p = L[i][p];
			}
		}
		st = x - dist;
	}
	{
		lint dist = 0;
		int p = x;
		for(int i=17; i>=0; i--){
			if(rank[R[i][p]] <= rank[y]){
				dist += DR[i][p];
				p = R[i][p];
			}
		}
		ed = x + dist;
	}
	lint Q = ed - ed % n + y;
	if(Q > ed) Q -= n;
	return Q >= st;
}
