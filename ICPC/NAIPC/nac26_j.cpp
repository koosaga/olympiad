#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 500005;
using line_t = lint;
const line_t is_query = -1e18;

struct Line {
	line_t m, b;
	mutable function<const Line *()> succ;
	bool operator<(const Line &rhs) const {
		if (rhs.b != is_query)
			return m < rhs.m;
		const Line *s = succ();
		if (!s)
			return 0;
		line_t x = rhs.m;
		return b - s->b < (__int128)(s->m - m) * x;
	}
};

struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
	bool bad(iterator y) {
		auto z = next(y);
		if (y == begin()) {
			if (z == end())
				return 0;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = prev(y);
		if (z == end())
			return y->m == x->m && y->b <= x->b;
		return (__int128)(x->b - y->b) * (z->m - y->m) >= (__int128)(y->b - z->b) * (y->m - x->m);
	}
	void insert_line(line_t m, line_t b) {
		auto y = insert({m, b});
		y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
		if (bad(y)) {
			erase(y);
			return;
		}
		while (next(y) != end() && bad(next(y)))
			erase(next(y));
		while (y != begin() && bad(prev(y)))
			erase(prev(y));
	}
	line_t query(line_t x) {
		auto l = *lower_bound((Line){x, is_query});
		return l.m * x + l.b;
	}
};

lint solve(vector<pi> a) {
	int n = sz(a);
	vector<lint> dp(n + 1);
	HullDynamic CH1, CH2;
	for (int i = 1; i <= n; i++) {
		CH1.insert_line(a[i - 1][0], dp[i - 1]);
		CH2.insert_line(a[i - 1][1], dp[i - 1]);
		dp[i] = max(CH1.query(a[i - 1][1]), CH2.query(a[i - 1][0]));

		/*
		for (int j = 0; j < i; j++) {
			dp[i] = max(dp[i], dp[j] + a[j][0] * a[i - 1][1]);
			dp[i] = max(dp[i], dp[j] + a[j][1] * a[i - 1][0]);
		}*/
	}
	return dp[n];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (auto &[w, h] : a)
		cin >> w >> h;
	rotate(a.begin(), max_element(all(a)), a.end());
	lint ans = solve(a);
	rotate(a.begin(), a.begin() + 1, a.end());
	ans = max(ans, solve(a));
	cout << ans << "\n";
}