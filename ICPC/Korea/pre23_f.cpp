#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int MAXN = 1000005;
const int MAXT = 4200000;

struct seg {
	pi tree[MAXT];
	int lazy[MAXT];
	pi merge(pi a, pi b) {
		if (a > b)
			swap(a, b);
		if (a[0] == b[0])
			b[1] += a[1];
		return b;
	}
	void init(int s, int e, int p, vector<int> &v) {
		if (s == e) {
			tree[p] = {0, v[s + 1] - v[s]};
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2 * p, v);
		init(m + 1, e, 2 * p + 1, v);
		tree[p] = merge(tree[2 * p], tree[2 * p + 1]);
	}
	void lazydown(int p) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			tree[i][0] += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			tree[p][0] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2 * p, v);
		add(s, e, pm + 1, pe, 2 * p + 1, v);
		tree[p] = merge(tree[2 * p], tree[2 * p + 1]);
	}
} seg;

struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int get_kth(int x) {
		if (x == 0)
			return 0;
		int pos = 0;
		for (int i = 19; i >= 0; i--) {
			if (pos + (1 << i) < MAXN && tree[pos + (1 << i)] < x) {
				pos += (1 << i);
				x -= tree[pos];
			}
		}
		return (pos - 1);
	}
} bit;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int l, n;
	cin >> l >> n;
	vector<int> c(n);
	vector<vector<pi>> v(n);
	for (auto &x : c)
		cin >> x;
	vector<int> vy;
	vy.push_back(-1);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int x, y, j;
		cin >> x >> y >> j;
		v[j - 1].push_back({x, y});
		vy.push_back(y);
	}
	sort(all(vy));
	vy.resize(unique(all(vy)) - vy.begin());
	auto coords = [&](int x) { return lower_bound(all(vy), x) - vy.begin(); };
	vector<array<int, 4>> events;
	auto addRect = [&](int sx, int ex, int sy, int ey) {
		if (sx <= ex && sy <= ey) {
			//	cout << sx << " " << ex << " " << sy << " " << ey << endl;
			events.push_back({sx, sy, ey + 1, +1});
			events.push_back({ex + 1, sy, ey + 1, -1});
		}
	};
	for (int i = 0; i < n; i++) {
		if (c[i] > sz(v[i]))
			continue;
		sort(all(v[i]));
		if (c[i] == 0) {
			int sx, ex, sy, ey;
			if (sz(v[i]) == 0) {
				sx = sy = 0, ex = ey = l;
			} else {
				sx = 0, ex = v[i][0][0] - 1;
				sy = 0, ey = l;
			}
			if (sx <= ex && sy <= ey) {
				//	cout << sx << " " << ex << " " << sy << " " << ey << endl;
				addRect(sx, ex, sy, ey);
			}
			if (sz(v[i]) > 0) {
				addRect(v[i][0][0], v[i][0][0], sy, min(ey, v[i][0][1] - 1));
			}
		}
		for (int j = 0; j < sz(v[i]); j++) {
			bit.add(coords(v[i][j][1]), +1);
			if (j + 1 >= c[i]) {

				int sx = v[i][j][0] + 1;
				int ex = (j + 1 < sz(v[i]) ? v[i][j + 1][0] : (l + 1)) - 1;
				int sy = vy[bit.get_kth(c[i])] + 1;
				int ey = (c[i] < j + 1 ? vy[bit.get_kth(c[i] + 1)] : (l + 1)) - 1;
				addRect(sx, ex, sy, ey);
				if (j + 1 < sz(v[i])) {
					addRect(v[i][j + 1][0], v[i][j + 1][0], sy, min(ey, v[i][j + 1][1] - 1));
				}
			}
		}
		for (int j = 0; j < sz(v[i]); j++) {
			bit.add(coords(v[i][j][1]), -1);
		}
	}
	if (sz(events) == 0) {
		cout << "0\n";
		return 0;
	}
	sort(all(events));
	vy.clear();
	for (auto &x : events) {
		vy.push_back(x[1]);
		vy.push_back(x[2]);
	}
	sort(all(vy));
	vy.resize(unique(all(vy)) - vy.begin());
	seg.init(0, sz(vy) - 2, 1, vy);
	lint ans = 0;
	for (int i = 0; i < sz(events); i++) {
		seg.add(coords(events[i][1]), coords(events[i][2]) - 1, 0, sz(vy) - 2, 1, events[i][3]);
		if (i + 1 < sz(events) && seg.tree[1][0] == n)
			ans += 1ll * seg.tree[1][1] * (events[i + 1][0] - events[i][0]);
	}
	cout << ans << "\n";
}