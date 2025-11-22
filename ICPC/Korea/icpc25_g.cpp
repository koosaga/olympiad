#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }
lint dot(pi a, pi b) { return a[0] * b[0] + a[1] * b[1]; }
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	lint x;
	cin >> n >> x;
	vector<pi> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i][0];
	for (int i = 0; i < n; i++)
		cin >> a[i][1];
	auto ok = [&](lint thr) { // after stuff min at least thr
		lint cur = 0;
		for (int i = 0; i < n; i++) {
			if (a[i][0] >= thr)
				continue;
			lint z = (thr - a[i][0] + a[i][1] - 1) / a[i][1];
			cur += z;
			if (cur >= x)
				return true;
		}
		return false;
	};
	lint s = 0, e = 2e18;
	while (s != e) {
		lint m = (s + e) / 2;
		if (ok(m))
			e = m;
		else
			s = m + 1;
	}
	lint q = s - 2;
	using node = array<lint, 3>;
	priority_queue<node, vector<node>, greater<node>> pq;
	for (int i = 0; i < n; i++) {
		if (a[i][0] >= q)
			continue;
		lint z = (q - a[i][0] + a[i][1] - 1) / a[i][1];
		x -= z;
		a[i][0] += z * a[i][1];
	}
	for (int i = 0; i < n; i++) {
		pq.push({a[i][0], i});
	}
	assert(x >= 0);
	for (int i = 0; i < x; i++) {
		auto tp = pq.top();
		pq.pop();
		a[tp[1]][0] += a[tp[1]][1];
		pq.push({a[tp[1]][0], tp[1]});
	}
	for (int i = 0; i < n; i++)
		cout << a[i][0] << " ";
}