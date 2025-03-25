#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

pi f(int r, int l, pi d) {
	if (r == 0)
		return d;
	auto [x, y] = d;
	return f(r - 1, l, pi{l - y, x});
}

vector<int> dp[166][4];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int l, n, t;
	cin >> l >> n >> t;
	l--;
	t /= 2;
	vector<pi> points(n);
	vector<pi> dx, dy;
	for (auto &[x, y] : points) {
		cin >> x >> y;
		x--;
		y--;
	}
	for (int i = 0; i < n; i++) {
		auto [x, y] = points[i];
		dx.push_back(pi{x + y, i});
		dy.push_back(pi{x - y, i});
	}
	dx.push_back(pi{-int(1e9), -1});
	dy.push_back(pi{-int(1e9), -1});
	sort(all(dx));
	sort(all(dy));
	for (int i = 0; i < sz(dx); i++) {
		vector<int> disc(n);
		vector<int> rev(n + 1);
		for (int j = 0; j < n; j++) {
			disc[j] = lower_bound(all(dy), pi{points[j][0] - points[j][1], j}) - dy.begin();
			rev[disc[j]] = j;
		}
		cr(dp[0][0], t + 1);
		cr(dp[0][1], t + 1);
		for (int j = 1; j <= n; j++) {
			int idx = rev[j];
			pi p{points[idx][0] + points[idx][1], idx};
			if (p <= dx[i]) {
				auto [x, y] = f(0, l, points[idx]);
				int d1 = abs(x) + abs(y);
				int d2 = abs(x) + abs(l - y);
				vector<int> nxt(t + 1, 1e9);
				for (int x = 0; x <= t; x++) {
					nxt[x] = min(nxt[x], dp[j - 1][0][x] + d2);
					if (x >= d1)
						nxt[x] = min(nxt[x], dp[j - 1][0][x - d1]);
				}
				dp[j][0] = nxt;
				dp[j][1] = dp[j - 1][1];
			} else {
				auto [x, y] = f(1, l, points[idx]);
				int d1 = abs(x) + abs(y);
				int d2 = abs(x) + abs(l - y);
				vector<int> nxt(t + 1, 1e9);
				for (int x = 0; x <= t; x++) {
					nxt[x] = min(nxt[x], dp[j - 1][1][x] + d2);
					if (x >= d1)
						nxt[x] = min(nxt[x], dp[j - 1][1][x - d1]);
				}
				dp[j][0] = dp[j - 1][0];
				dp[j][1] = nxt;
			}
		}
		cr(dp[n][2], t + 1);
		cr(dp[n][3], t + 1);
		for (int j = n - 1; j >= 0; j--) {
			int idx = rev[j + 1];
			pi p{points[idx][0] + points[idx][1], idx};
			if (p <= dx[i]) {
				auto [x, y] = f(3, l, points[idx]);
				int d1 = abs(x) + abs(y);
				int d2 = abs(x) + abs(l - y);
				vector<int> nxt(t + 1, 1e9);
				for (int x = 0; x <= t; x++) {
					nxt[x] = min(nxt[x], dp[j + 1][3][x] + d2);
					if (x >= d1)
						nxt[x] = min(nxt[x], dp[j + 1][3][x - d1]);
				}
				dp[j][3] = nxt;
				dp[j][2] = dp[j + 1][2];
			} else {
				auto [x, y] = f(2, l, points[idx]);
				int d1 = abs(x) + abs(y);
				int d2 = abs(x) + abs(l - y);
				vector<int> nxt(t + 1, 1e9);
				for (int x = 0; x <= t; x++) {
					nxt[x] = min(nxt[x], dp[j + 1][2][x] + d2);
					if (x >= d1)
						nxt[x] = min(nxt[x], dp[j + 1][2][x - d1]);
				}
				dp[j][3] = dp[j + 1][3];
				dp[j][2] = nxt;
			}
		}
		for (int j = 0; j < sz(dy); j++) {
			bool ok = 0;
			for (int x = 0; x <= t; x++) {
				if (dp[j][0][x] > t)
					continue;
				int b1 = t - dp[j][0][x];
				if (dp[j][1][b1] > t)
					continue;
				int b2 = t - dp[j][1][b1];
				if (dp[j][2][b2] > t)
					continue;
				int b3 = t - dp[j][2][b2];
				if (dp[j][3][b3] > t - x)
					continue;
				ok = 1;
			}
			if (ok) {
				cout << "Yes\n";
				return 0;
			}
		}
	}
	cout << "No\n";
}