#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
using line_t = __int128;
const line_t is_query = -5e18;

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
		return b - s->b < (s->m - m) * x;
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
		return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	vector<pi> a(m);
	for (auto &[x, y] : a)
		cin >> x >> y;
	vector<int> queries(q);
	vector<lint> ans(q, 2e18);
	auto solve = [&]() {
		vector<array<lint, 3>> b(m);
		for (int i = 0; i < m; i++) {
			b[i][0] = a[i][0];
			b[i][1] = a[i][1];
			b[i][2] = i;
		}
		sort(all(b));
		int mpos = 0;
		for (int i = 0; i < m; i++)
			if (b[i][2] == m - 1)
				mpos = i;
		vector<lint> dp(m);
		HullDynamic ch1;
		for (int i = m - 1; i >= 0; i--) {
			if (i >= mpos) {
				dp[i] = (b[mpos][0] - b[i][0]) * b[i][1];
				continue;
			}
			ch1.insert_line(-b[i + 1][0], -dp[i + 1]);
			dp[i] = -ch1.query(b[i][1]) - b[i][0] * b[i][1];
		}
		vector<int> ord(sz(queries));
		iota(all(ord), 0);
		sort(all(ord), [&](int x, int y) { return queries[x] > queries[y]; });
		priority_queue<pi, vector<pi>, greater<pi>> pq;
		for (int i = 0; i < m; i++) {
			pq.push({dp[i], b[i][0]});
		}
		ch1.clear();
		int j = m;
		for (auto &i : ord) {
			if (queries[i] > b[mpos][0])
				continue;
			ans[i] = min(ans[i], (b[mpos][0] - queries[i]) * b[mpos][1]);
			while (sz(pq) && pq.top()[1] > queries[i])
				pq.pop();
			if (sz(pq))
				ans[i] = min(ans[i], pq.top()[0]);
			while (j && b[j - 1][0] > queries[i]) {
				j--;
				ch1.insert_line(2 * b[j][1], -dp[j] - 2 * b[j][0] * b[j][1]);
			}
			if (ch1.size())
				ans[i] = min(ans[i], -(lint)ch1.query(queries[i]));
		}
	};
	for (auto &x : queries)
		cin >> x;
	solve();
	for (auto &[x, y] : a)
		x = n + 1 - x;
	for (auto &x : queries)
		x = n + 1 - x;
	solve();
	for (auto &x : ans)
		cout << x << "\n";
}