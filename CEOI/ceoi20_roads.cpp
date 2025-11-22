#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
const int inf = 1e8;

struct line {
	pi p, q;
	int idx;
	llf f(int x) const {
		if (p[0] == q[0])
			return p[1];
		return 1.0L * (p[1] * (q[0] - x) + q[1] * (x - p[0])) / (q[0] - p[0]);
	}
	bool operator<(const line &l) const {
		int x = max(p[0], l.p[0]);
		return f(x) < l.f(x);
	}
};

struct node {
	pi p;
	int idx, is_del;
	bool operator<(const node &nd) const { return p < nd.p; }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<line> a(n);
	vector<node> events;
	for (int i = 0; i < n; i++) {
		cin >> a[i].p[0] >> a[i].p[1] >> a[i].q[0] >> a[i].q[1];
		if (a[i].p > a[i].q)
			swap(a[i].p, a[i].q);
		a[i].idx = i;
		events.push_back({a[i].p, i, 0});
		events.push_back({a[i].q, i, 1});
	}
	sort(all(events));
	set<line> sweeps;
	sweeps.insert(line{pi{-inf, -inf}, pi{inf, -inf}, n});
	vector<pi> nxt(n + 1);
	auto pr = [&](pi p, pi c) { cout << p[0] << " " << p[1] << " " << c[0] << " " << c[1] << "\n"; };
	for (int i = 0; i < sz(events); i++) {
		if (i == 0) {
			sweeps.insert(a[events[i].idx]);
			nxt[n] = events[i].p;
			nxt[events[i].idx] =
				(a[events[i].idx].p[0] == a[events[i].idx].q[0] ? a[events[i].idx].q : a[events[i].idx].p);
			continue;
		}
		if (events[i].is_del == 0) {
			auto it = sweeps.lower_bound(a[events[i].idx]);
			pr(nxt[prev(it)->idx], events[i].p);
			nxt[prev(it)->idx] = events[i].p;
			sweeps.insert(a[events[i].idx]);
			nxt[events[i].idx] =
				(a[events[i].idx].p[0] == a[events[i].idx].q[0] ? a[events[i].idx].q : a[events[i].idx].p);
		} else {
			sweeps.erase(a[events[i].idx]);
			auto it = sweeps.lower_bound(a[events[i].idx]);
			nxt[prev(it)->idx] = events[i].p;
		}
	}
}