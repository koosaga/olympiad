#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct pt {
	int x, y, dx;
};

int ccw(pt a, pt b) {
	long long t = 1ll * a.x * b.y - 1ll * b.x * a.y;
	if (t > 0)
		return 1;
	if (t < 0)
		return -1;
	return 0;
}

bool cmp(pt a, pt b) { return ccw(a, b) > 0; }

vector<pt> v;

int n;

int main() {
	int X, Y;
	scanf("%d %d", &X, &Y);
	scanf("%d", &n);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int sx, sy, ex, ey;
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		if (min(sx, ex) == 0 && min(sy, ey) == 0) {
			cnt++;
			continue;
		}
		v.push_back({min(sx, ex), max(sy, ey), -1});
		v.push_back({max(sx, ex), min(sy, ey), 1});
	}
	sort(v.begin(), v.end(), cmp);
	auto order = [&](int k) {
		if (k <= Y)
			return pt{X, k, -1};
		k -= Y;
		if (k <= X)
			return pt{X - k, Y, -1};
		return pt{-1, -1, -1};
	};
	int ans = 0;
	pt P = {X, Y, -1};
	auto updateSingle = [&](int val, pt p) {
		lint s = 0, e = X + Y + 1;
		while (s != e) {
			lint m = (s + e) / 2;
			if (ccw(p, order(m)) >= 0)
				e = m;
			else
				s = m + 1;
		}
		if (s <= X + Y && ccw(p, order(s)) == 0) {
			if (ans < val) {
				ans = val;
				P = order(s);
			}
		}
	};
	auto updateOpen = [&](int val, pt p, pt q) {
		lint s = 0, e = X + Y + 1;
		while (s != e) {
			lint m = (s + e) / 2;
			if (ccw(p, order(m)) > 0)
				e = m;
			else
				s = m + 1;
		}
		if (s <= X + Y && ccw(order(s), q) > 0) {
			if (ans < val) {
				ans = val;
				P = order(s);
			}
		}
	};
	int ret = 0, cur = 0;
	for (int i = 0; i < v.size();) {
		int e = i;
		while (e < v.size() && ccw(v[e], v[i]) == 0) {
			e++;
		}
		for (int j = i; j < e; j++) {
			if (v[j].dx == 1)
				cur++;
		}
		updateSingle(cur, v[i]);
		for (int j = i; j < e; j++) {
			if (v[j].dx == -1)
				cur--;
		}
		if (e < sz(v))
			updateOpen(cur, v[i], v[e]);
		i = e;
	}
	printf("%d %d %d", ans + cnt, P.x, P.y);
}