#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct node {
	int x, y, d;
};

struct bucket {
	vector<int> rowRanges[4];
	int n, m;
	void init(int _n, int _m) {
		n = _n;
		m = _m;
		for (int i = 0; i < 4; i++) {
			rowRanges[i].resize(n, 0);
		}
	}
	void popRanges(int sx, int ex, int sy, int ey, vector<pi> &ans) {
		auto Do = [&](int ex, int ey, int v) {
			for (int i = ex - 1; i >= 0; i--) {
				if (rowRanges[v][i] >= ey)
					break;
				while (rowRanges[v][i] < ey) {
					ans.push_back({i, rowRanges[v][i]});
					rowRanges[v][i]++;
				}
			}
		};
		if (sx == 0 && sy == 0) {
			Do(ex - sx, ey - sy, 0);
		} else if (ex == n && sy == 0) {
			Do(ex - sx, ey - sy, 1);
			for (auto &[x, y] : ans)
				x = n - x - 1;
		} else if (sx == 0 && ey == m) {
			Do(ex - sx, ey - sy, 2);
			for (auto &[x, y] : ans)
				y = m - y - 1;
		} else if (ex == n && ey == m) {
			Do(ex - sx, ey - sy, 3);
			for (auto &[x, y] : ans) {
				x = n - x - 1;
				y = m - y - 1;
			}
		} else
			assert(0);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, g;
	cin >> n >> m >> g;
	pi s, t;
	cin >> s[0] >> s[1] >> t[0] >> t[1];
	s[0]--;
	s[1]--;
	t[0]--;
	t[1]--;
	vector<string> v(n);
	for (auto &x : v)
		cin >> x;
	deque<array<int, 3>> dq;
	vector<vector<int>> dist(n, vector<int>(m, 1e9));
	auto enq = [&](int x, int y, int d) {
		if (dist[x][y] > d) {
			dist[x][y] = d;
			dq.push_back({x, y, d});
		}
	};
	auto enqf = [&](int x, int y, int d) {
		if (dist[x][y] > d) {
			dist[x][y] = d;
			dq.push_front({x, y, d});
		}
	};
	int dn = (n + 2 * g - 2) / (2 * g - 1);
	int dm = (m + 2 * g - 2) / (2 * g - 1);
	if (g == 1)
		dn = dm = 1;
	vector<vector<bucket>> buck(dn, vector<bucket>(dm));
	if (g > 1) {
		for (int i = 0; i < dn; i++) {
			for (int j = 0; j < dm; j++) {
				int zn = n - i * (2 * g - 1);
				int zm = m - j * (2 * g - 1);
				zn = min(zn, 2 * g - 1);
				zm = min(zm, 2 * g - 1);
				buck[i][j].init(zn, zm);
			}
		}
	}
	auto ok = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; };
	enq(s[0], s[1], 0);
	while (sz(dq)) {
		auto [x, y, d] = dq.front();
		dq.pop_front();
		if (dist[x][y] != d)
			continue;
		for (int i = 0; i < 4; i++) {
			if (ok(x + dx[i], y + dy[i]) == 0)
				continue;
			if (v[x + dx[i]][y + dy[i]] == '.')
				enqf(x + dx[i], y + dy[i], d);
			else if (g == 1) {
				enq(x + dx[i], y + dy[i], d + 1);
				continue;
			}
			int bx = max(x + dx[i] - g + 1, 0) / (2 * g - 1);
			int by = max(y + dy[i] - g + 1, 0) / (2 * g - 1);
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					if (bx + j >= dn || by + k >= dm)
						continue;
					int sx = x + dx[i] - g + 1;
					int ex = x + dx[i] + g;
					int sy = y + dy[i] - g + 1;
					int ey = y + dy[i] + g;
					sx -= (bx + j) * (2 * g - 1);
					ex -= (bx + j) * (2 * g - 1);
					sy -= (by + k) * (2 * g - 1);
					ey -= (by + k) * (2 * g - 1);
					sx = max(sx, 0);
					ex = min(ex, buck[bx + j][by + k].n);
					sy = max(sy, 0);
					ey = min(ey, buck[bx + j][by + k].m);
					if (sx >= ex || sy >= ey)
						continue;
					vector<pi> ret;
					buck[bx + j][by + k].popRanges(sx, ex, sy, ey, ret);
					for (auto &[zx, zy] : ret)
						enq(zx + (bx + j) * (2 * g - 1), zy + (by + k) * (2 * g - 1), d + 1);
				}
			}
		}
	}
	cout << dist[t[0]][t[1]] << "\n";
}