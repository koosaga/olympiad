#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 500005;
 
struct rect{
	int s, e, x, idx;
	rect operator*(const rect &r)const{
		return {max(s, r.s), min(e, r.e), min(x, r.x)};
	}
	lint area() const{
		return 1ll * x * (e - s + 1);
	}
};

using line_t = lint;
const line_t is_query = -1e18;

struct Line {
	line_t m, b;
	mutable function<const Line*()> succ;
	bool operator<(const Line& rhs) const {
		if (rhs.b != is_query) return m < rhs.m;
		const Line* s = succ();
		if (!s) return 0;
		line_t x = rhs.m;
		return b - s->b < (s->m - m) * x;
	}
};

struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
	bool bad(iterator y) {
		auto z = next(y);
		if (y == begin()) {
			if (z == end()) return 0;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = prev(y);
		if (z == end()) return y->m == x->m && y->b <= x->b;
		return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
	}
	void add(line_t m, line_t b) {
		auto y = insert({ m, b });
		y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
		if (bad(y)) { erase(y); return; }
		while (next(y) != end() && bad(next(y))) erase(next(y));
		while (y != begin() && bad(prev(y))) erase(prev(y));
	}
	line_t query(line_t x) {
		if(size() == 0) return -1e18;
		auto l = *lower_bound((Line) { x, is_query });
		return l.m * x + l.b;
	}
}cht;

lint ccw(pi a, pi b, pi c){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

lint ccw(pi a, pi b){
	return ccw(pi(0, 0), a, b);
}

lint dist(pi a, pi b){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	return dx1 * dx1 + dy1 * dy1;
}

vector<pi> cvxp(vector<rect> r){
	vector<pi> point;
	for(auto &x : r){
		point.emplace_back(x.e - x.s + 1, x.area());
	}
	vector<pi> stk = {pi(0, 0)};
	vector<pi> slopes;
	for(auto &i : point){
		while(sz(stk) >= 2 && ccw(stk[sz(stk) - 2], stk.back(), i) >= 0) stk.pop_back();
		stk.push_back(i);
	}
	for(int i = 1; i < sz(stk); i++){
		if(stk[i].second <= stk[i - 1].second) break;
		slopes.emplace_back(stk[i].first - stk[i-1].first, stk[i].second - stk[i-1].second);
	}
	return slopes;
}

void get_maxH(int s, int e, vector<rect> &vs, vector<rect> &ve, vector<lint> &maxH){
	if(s == e) return;
	int m = (s + e) / 2;
	vector<rect> ls, rs, le, re;
	// recurse here
	{
		for(auto &i : vs){
			if(i.s <= m) ls.push_back(i);
			else rs.push_back(i);
		}
		for(auto &i : ve){
			if(i.e <= m) le.push_back(i);
			else re.push_back(i);
		}
		get_maxH(s, m, ls, le, maxH);
		get_maxH(m+1, e, rs, re, maxH);
		merge(all(ls), all(rs), vs.begin(), [&](const rect &a, const rect &b){
			return pi(a.e - a.s, a.area()) < pi(b.e - b.s, b.area());
		});
		merge(all(le), all(re), ve.begin(), [&](const rect &a, const rect &b){
			return pi(a.e - a.s, a.area()) < pi(b.e - b.s, b.area());
		});
	}
	// should maximize A - x H for some x
	vector<pi> c1 = cvxp(le);
	vector<pi> c2 = cvxp(rs);
	vector<pi> c3(sz(c1) + sz(c2));
	merge(all(c1), all(c2), c3.begin(), [&](const pi &a, const pi &b){
		return ccw(a, b) < 0;
	});
	for(int i = 0; i < sz(c3); i++){
		if(i > 0){
			c3[i].first += c3[i - 1].first;
			c3[i].second += c3[i - 1].second;
		}
		maxH[c3[i].first] = max(maxH[c3[i].first], c3[i].second);
	}
}

vector<lint> max_area(vector<int> H) {
	int n = sz(H);
	H.push_back(0);
	vector<int> stk;
	vector<rect> v;
	for(int i = 0; i <= n; i++){
		while(sz(stk) && H[stk.back()] > H[i]){
			int h = H[stk.back()];
			stk.pop_back();
			int l = sz(stk) ? stk.back() : -1;
			int r = i;
			v.push_back({l + 1, r - 1, h});
		}
		stk.push_back(i);
	}
	vector<lint> R(3);
	for(int i = 0; i < sz(v); i++){
		v[i].idx = i;
		R[0] = max(R[0], v[i].area());
	}
	sort(all(v), [&](const rect &a, const rect &b){
		return pi(a.e, -a.s) < pi(b.e, -b.s);
	});
	vector<lint> F(sz(v)), G(sz(v));
	vector<lint> pmax(n), smax(n);
	cht.clear();
	for(int i = 0; i < sz(v); i++){	
		F[v[i].idx] = max(F[v[i].idx], v[i].area() + cht.query(v[i].x));
		cht.add(-(v[i].e - v[i].s + 1), v[i].area());
		pmax[v[i].e] = max(pmax[v[i].e], v[i].area());
		smax[v[i].s] = max(smax[v[i].s], v[i].area());
	}
	sort(all(v), [&](const rect &a, const rect &b){
		return pi(-a.s, a.e) < pi(-b.s, b.e);
	});
	cht.clear();
	for(int i = 0; i < sz(v); i++){	
		G[v[i].idx] = max(G[v[i].idx], v[i].area() + cht.query(v[i].x));
		cht.add(-(v[i].e - v[i].s + 1), v[i].area());
	}
	cht.clear();
	sort(all(v), [&](const rect &a, const rect &b){
		return pi(a.e, -a.s) < pi(b.e, -b.s);
	});
	for(int i = 1; i < n; i++) pmax[i] = max(pmax[i], pmax[i - 1]);
	for(int i = n-2; i >= 0; i--) smax[i] = max(smax[i], smax[i + 1]);
	for(auto &i : v){
		R[1] = max(R[1], F[i.idx]);
		if(i.s > 0) R[1] = max(R[1], i.area() + pmax[i.s - 1]);
	}
	for(int i = 0; i < sz(v); i++){
		// case 1: [][][]
		if(v[i].s > 0 && v[i].e < n - 1){
			R[2] = max(R[2], v[i].area() + pmax[v[i].s - 1] + smax[v[i].e + 1]);
		}
		// case 2: [[]][] or vice versa
		if(v[i].e < n - 1) R[2] = max(R[2], F[v[i].idx] + smax[v[i].e + 1]);
		if(v[i].s > 0) R[2] = max(R[2], G[v[i].idx] + pmax[v[i].s - 1]);
		// case 3: [[[]]]
		R[2] = max(R[2], v[i].area() + cht.query(v[i].x));
		cht.add(-(v[i].e - v[i].s + 1), F[v[i].idx]);
	}
	cht.clear();
	// case 4: [[][]]
	vector<lint> maxH(n + 1);
	auto vByStart = v;
	auto vByEnd = v;
	get_maxH(0, n-1, vByStart, vByEnd, maxH);
	for(int j = 1; j <= n; j++) cht.add(-j, maxH[j]);
	for(int i = 0; i < sz(v); i++){
		R[2] = max(R[2], v[i].area() + cht.query(v[i].x));
	}
	R[1] = max(R[1], R[0]);
	R[2] = max(R[2], R[1]);
	return R;
}
