#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <numeric>
#include <functional>
#include <tuple>
#include <complex>
#include <bitset>
#include <random>

using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct line {
	int dx, l, idx;
	bool operator<(const line &m)const {
		return pi(-dx, l) < pi(-m.dx, m.l);
	}
};

int sx, ex, n;
vector<line> v, h;

bool bad(line a, line b, line c) {
	return 1ll * (b.l - a.l) * (b.dx - c.dx) > 1ll * (c.l - b.l) * (a.dx - b.dx);
	// fucking decreasing order
	return (b.l - a.l) / (a.dx - b.dx) > (c.l - b.l) / (b.dx - c.dx);
}

lint func(line l, lint x) {
	return 1ll * l.dx * (x - sx * 1000) + 1000ll * l.l * (ex - sx);
}

int main() {
	cin >> ex >> sx >> n;
	for (int i = 1; i <= n; i++) {
		int y1, y2;
		scanf("%d %d", &y2, &y1);
		v.push_back({ y2 - y1, y1, i });
	}
	sort(v.begin(), v.end());
	for (auto &i : v) {
		if (!h.empty() && h.back().dx == i.dx) continue;
		while (h.size() >= 2 && bad(h[h.size() - 2], h.back(), i)) h.pop_back();
		h.push_back(i);
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		double k; scanf("%lf", &k);
		lint w = (int)round(1000 * k);
		int s = 0, e = h.size() - 1;
		while (s != e) {
			int m = (s + e) / 2;
			if (func(h[m], w) < func(h[m + 1], w)) e = m;
			else s = m + 1;
		}
		printf("%d\n", h[s].idx);
	}
}
