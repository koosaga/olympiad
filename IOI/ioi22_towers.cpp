#include "towers.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 270000;
const int inf = 1e9;

struct segmax{
	pi tree[MAXT];
	int lim;
	void init(vector<int> &a){
		for(lim = 1; lim <= sz(a); lim <<= 1);
		for(int i = 0; i < sz(a); i++){
			tree[i + lim] = pi(a[i], i);
		}
		for(int i = lim-1; i; i--) tree[i] = max(tree[2*i], tree[2*i+1]);
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(0, 0);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}segmax;

struct segmin{
	pi tree[MAXT];
	int lim;
	void init(vector<int> &a){
		for(lim = 1; lim <= sz(a); lim <<= 1);
		fill(tree, tree + MAXT, pi(inf, inf));
		for(int i = 0; i < sz(a); i++){
			tree[i + lim] = pi(a[i], i);
		}
		for(int i = lim-1; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(inf, inf);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}segmin;

struct node{
	int l, r;
	int cnt, lmo, rmo;
};

node tree[2000000];
int piv;

int newnode(){
	return ++piv;
}

void init(int s, int e, int p){
	tree[p].cnt = 0;
	tree[p].lmo = inf, tree[p].rmo = -inf;
	if(s == e) return;
	int m = (s + e) / 2;
	tree[p].l = newnode();
	tree[p].r = newnode();
	init(s, m, tree[p].l);
	init(m+1, e, tree[p].r);
}

node merge(node a, node x, node y){
	a.cnt = x.cnt + y.cnt;
	a.lmo = min(x.lmo, y.lmo);
	a.rmo = max(x.rmo, y.rmo);
	return a;
}

void add(int s, int e, int v, int p1, int p2){
	if(s == e){
		tree[p2].cnt = tree[p1].cnt + 1;
		tree[p2].lmo = min(tree[p1].lmo, v);
		tree[p2].rmo = max(tree[p1].rmo, v);
		return;
	}
	int m = (s + e) / 2;
	if(v <= m){
		tree[p2].l = newnode();
		tree[p2].r = tree[p1].r;
		add(s, m, v, tree[p1].l, tree[p2].l);
	}
	else{
		tree[p2].r = newnode();
		tree[p2].l = tree[p1].l;
		add(m+1, e, v, tree[p1].r, tree[p2].r);
	}
	tree[p2] = merge(tree[p2], tree[tree[p2].l], tree[tree[p2].r]);
}

node query(int s, int e, int ps, int pe, int p){
	if(e < ps || pe < s) return (node){0, 0, 0, inf, -inf};
	if(s <= ps && pe <= e) return tree[p];
	int pm = (ps+pe)/2;
	auto x = query(s, e, ps, pm, tree[p].l);
	auto y = query(s, e, pm+1, pe, tree[p].r);
	return merge(x, x, y);
}

vector<int> root;
vector<int> a;

struct foo{
	int val, x, y;
	bool operator<(const foo &nd)const{
		return val > nd.val;
	}
};

vector<pi> points;

void init(int N, std::vector<int> H) {
	if(N <= 2) return;
	a = H;
	segmax.init(H);
	segmin.init(H);
	vector<int> v;
	set<int> s;
	v.push_back(0);
	for(int i = 1; i + 1 < N; i++){
		if((H[i - 1] < H[i]) != (H[i] < H[i + 1])) v.push_back(i);
	}
	v.push_back(N - 1);
	if(H[v[0]] > H[v[1]]) v.erase(v.begin());
	if(sz(v) >= 2 && H[v[sz(v) - 2]] < H[v.back()]) v.pop_back();
	for(auto &x : v){
		s.insert(x);
	}
	priority_queue<foo> pq;
	for(int i = 1; i < sz(v); i++){
		pq.push({abs(H[v[i]] - H[v[i - 1]]), v[i - 1], v[i]});
	}
	while(sz(pq)){
		auto x = pq.top();
		pq.pop();
		if(!s.count(x.x) || !s.count(x.y)) continue;
		s.erase(x.x);
		s.erase(x.y);
		auto prv = s.lower_bound(x.x);
		auto nxt = s.upper_bound(x.y);
		if(H[x.x] < H[x.y]) points.emplace_back(x.val, x.x);
		else points.emplace_back(x.val, x.y);
		if(prv != s.begin() && nxt != s.end()){
			prv--;
			pq.push({abs(H[*prv] - H[*nxt]), *prv, *nxt});
		}
	}
	points.emplace_back(2e9, *s.begin());
	reverse(all(points));
	root.resize(sz(points) + 1);
	root[0] = newnode();
	init(0, sz(a) - 1, root[0]);
	for(int i = 0; i < sz(points); i++){
		root[i + 1] = newnode();
		add(0, sz(a) - 1, points[i].second, root[i], root[i + 1]);
	}
}

tuple<int, int, int> query(int L, int R, int D){
	int s = 0, e = sz(points);
	while(s != e){
		int m = (s + e) / 2;
		if(points[m].first >= D) s = m + 1;
		else e = m;
	}
	auto qr = query(L, R, 0, sz(a) - 1, root[s]);
	return make_tuple(qr.cnt, qr.lmo, qr.rmo);
}

int max_towers(int L, int R, int D) {
	if(R - L <= 1) return 1;
	auto [cnt, leftmost, rightmost] = query(L, R, D);
	if(cnt == 0){
		auto qr = segmax.query(L, R);
		if(segmin.query(L, qr.second - 1).first <= qr.first - D && segmin.query(qr.second + 1, R).first <= qr.first - D){
			return 2;
		}
		return 1;
	}
	else{
		int ans = cnt;
		{
			auto qr = segmax.query(L, leftmost);
			if(segmin.query(L, qr.second - 1).first <= qr.first - D) ans++;
		}
		{
			auto qr = segmax.query(rightmost, R);
			if(segmin.query(qr.second + 1, R).first <= qr.first - D) ans++;
		}
		return ans;
	}
}
