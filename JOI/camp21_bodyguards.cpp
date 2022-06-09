#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int MAXN = 6000;

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
		return b - s->b < (__int128)(s->m - m) * x;
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
		return (__int128)(x->b - y->b)*(z->m - y->m) >= (__int128)(y->b - z->b)*(y->m - x->m);
	}
	void insert_line(line_t m, line_t b) {
		auto y = insert({ m, b });
		y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
		if (bad(y)) { erase(y); return; }
		while (next(y) != end() && bad(next(y))) erase(next(y));
		while (y != begin() && bad(prev(y))) erase(prev(y));
	}
	line_t query(line_t x) {
		auto l = *lower_bound((Line) { x, is_query });
		return l.m * x + l.b;
	}
};

struct seg{
	lint pos, s, e, x;
};

struct query{
	lint i, j, idx, pos;
};

lint R[MAXN][MAXN], D[MAXN][MAXN], dp[MAXN][MAXN];
vector<query> downQuery, rightQuery;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	vector<seg> ho, ve;
	int n, q;
	cin >> n >> q;
	for(int i = 0; i < n; i++){
		lint t, a, b, c; cin >> t >> a >> b >> c;
		if(a < b){
			ho.push_back({t - a, t + a, t + a + 2 * (b - a), c});
		}
		else{
			ve.push_back({t + a, t - a, t - a - 2 * (b - a), c});
		}
	}
	vector<lint> vx, vy;
	vx.push_back(-1e10);
	vy.push_back(-1e10);
	for(auto &x : ho){
		vx.push_back(x.pos);
		vy.push_back(x.s);
		vy.push_back(x.e);
	}
	for(auto &x : ve){
		vy.push_back(x.pos);
		vx.push_back(x.s);
		vx.push_back(x.e);
	}
	sort(all(vx)); vx.resize(unique(all(vx)) - vx.begin());
	sort(all(vy)); vy.resize(unique(all(vy)) - vy.begin());
	for(auto &x : ho){
		x.pos = lower_bound(all(vx), x.pos) - vx.begin();
		x.s = lower_bound(all(vy), x.s) - vy.begin();
		x.e = lower_bound(all(vy), x.e) - vy.begin();
		for(int i = x.s; i < x.e; i++) R[x.pos][i] = max(R[x.pos][i], x.x);
	}
	for(auto &x : ve){
		x.pos = lower_bound(all(vy), x.pos) - vy.begin();
		x.s = lower_bound(all(vx), x.s) - vx.begin();
		x.e = lower_bound(all(vx), x.e) - vx.begin();
		for(int i = x.s; i < x.e; i++) D[i][x.pos] = max(D[i][x.pos], x.x);
	}
	for(int i = sz(vx) - 1; i >= 0; i--){
		for(int j = sz(vy) - 1; j >= 0; j--){
			if(i + 1 < sz(vx)) dp[i][j] = max(dp[i][j], dp[i + 1][j] + (vx[i + 1] - vx[i]) * D[i][j]);
			if(j + 1 < sz(vy)) dp[i][j] = max(dp[i][j], dp[i][j + 1] + (vy[j + 1] - vy[j]) * R[i][j]);
		}
	}
	vector<lint> ret(q);
	for(int idx = 0; idx < q; idx++){
		lint P, X; cin >> P >> X;
		tie(P, X) = pi(P - X, P + X);
		int i = lower_bound(all(vx), P) - vx.begin();
		int j = lower_bound(all(vy), X) - vy.begin();
		if(i < sz(vx) && j < sz(vy)){
			rightQuery.push_back({i, j, idx, -X});
			downQuery.push_back({i, j, idx, -P});
		}
	}
	sort(all(downQuery), [&](const query &a, const query &b){
		return pi(a.i, a.j) > pi(b.i, b.j);
	});
	sort(all(rightQuery), [&](const query &a, const query &b){
		return pi(a.j, a.i) > pi(b.j, b.i);
	});
	int p; 
	p = 0;
	for(int i = sz(vx) - 1; i > 0; i--){	
		HullDynamic cht;
		for(int j = sz(vy) - 1; j > 0; j--){
			cht.insert_line(D[i-1][j], dp[i][j] + vx[i] * D[i-1][j]);
			while(p < sz(downQuery) && downQuery[p].i == i && downQuery[p].j == j){
				auto q = downQuery[p++];
				ret[q.idx] = max(ret[q.idx], cht.query(q.pos));
			}
		}
	}
	p = 0;
	for(int j = sz(vy) - 1; j > 0; j--){
		HullDynamic cht;
		for(int i = sz(vx) - 1; i > 0; i--){
			cht.insert_line(R[i][j-1], dp[i][j] + vy[j] * R[i][j-1]);
			while(p < sz(rightQuery) && rightQuery[p].i == i && rightQuery[p].j == j){
				auto q = rightQuery[p++];
				ret[q.idx] = max(ret[q.idx], cht.query(q.pos));
			}
		}
	}
	for(int i = 0; i < q; i++) cout << ret[i] / 2 << "\n";
}
