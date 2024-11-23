#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

struct hpi {
	const double eps = 1e-8;
	typedef pair<long double, long double> pi;
	bool z(long double x) const { return fabs(x) < eps; }
	long double ccw(pi a, pi b, pi c) {
		long double dx1 = b.first - a.first;
		long double dy1 = b.second - a.second;
		long double dx2 = c.first - a.first;
		long double dy2 = c.second - a.second;
		return dx1 * dy2 - dy1 * dx2;
	}
	struct line {
		long double a, b, c;
		pi slope() { return pi(a, b); }
	};
	pi cross(line a, line b) {
		long double det = a.a * b.b - b.a * a.b;
		return pi((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
	}
	bool bad(line a, line b, line c) {
		if (ccw(pi(0, 0), a.slope(), b.slope()) <= 0)
			return false;
		pi crs = cross(a, b);
		return crs.first * c.a + crs.second * c.b >= c.c;
	}
	bool solve(vector<line> v, vector<pi> &solution) { // ax + by <= c;
		sort(v.begin(), v.end(), [&](line &fuck, line &l) {
			auto [a, b, c] = make_tuple(fuck.a, fuck.b, fuck.c);
			bool flag1 = pi(a, b) > pi(0, 0);
			bool flag2 = pi(l.a, l.b) > pi(0, 0);
			if (flag1 != flag2)
				return flag1 > flag2;
			long double t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
			return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
		});
		deque<line> dq;
		for (auto &i : v) {
			if (!dq.empty() && z(ccw(pi(0, 0), dq.back().slope(), i.slope())))
				continue;
			while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), i))
				dq.pop_back();
			while (dq.size() >= 2 && bad(i, dq[0], dq[1]))
				dq.pop_front();
			dq.push_back(i);
		}
		while (dq.size() > 2 && bad(dq[dq.size() - 2], dq.back(), dq[0]))
			dq.pop_back();
		while (dq.size() > 2 && bad(dq.back(), dq[0], dq[1]))
			dq.pop_front();
		vector<pi> tmp;
		for (int i = 0; i < dq.size(); i++) {
			line cur = dq[i], nxt = dq[(i + 1) % dq.size()];
			if (ccw(pi(0, 0), cur.slope(), nxt.slope()) <= eps)
				return false;
			tmp.push_back(cross(cur, nxt));
		}
		solution = tmp;
		return true;
	}
} hpi;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int w, h, n;
	cin >> w >> h >> n;
	vector<hpi::line> v;
	v.push_back({-1, 0, 0});
	v.push_back({0, -1, 0});
	v.push_back({1, 0, 1.0L * w});
	v.push_back({0, 1, 1.0L * h});
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y;
	vector<int> p(n);
	for (int i = 0; i < n; i++)
		cin >> p[i], p[i]--;
	reverse(all(p));
	for (int i = 1; i < n; i++) {
		pi x = a[p[0]], y = a[p[i]];
		v.push_back({1.0L * y[1] - 1.0L * x[1], 1.0L * x[0] - 1.0L * y[0], 1.0L * x[0] * y[1] - 1.0L * x[1] * y[0]});
	}
	for (int i = 0; i + 1 < n; i++) {
		pi x = a[p[i]], y = a[p[n - 1]];
		v.push_back({1.0L * y[1] - 1.0L * x[1], 1.0L * x[0] - 1.0L * y[0], 1.0L * x[0] * y[1] - 1.0L * x[1] * y[0]});
	}
	for (int i = 0; i + 1 < n; i++) {
		pi x = a[p[i]], y = a[p[i + 1]];
		v.push_back({1.0L * y[1] - 1.0L * x[1], 1.0L * x[0] - 1.0L * y[0], 1.0L * x[0] * y[1] - 1.0L * x[1] * y[0]});
	}
	vector<hpi::pi> ans;
	if (!hpi.solve(v, ans)) {
		cout << "0\n";
		return 0;
	}
	long double dap = 0;
	for (int i = 2; i < sz(ans); i++) {
		dap += hpi.ccw(ans[0], ans[i - 1], ans[i]);
	}
	cout << setprecision(69) << dap / 2 << "\n";
}