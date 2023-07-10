#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pi>> points(MAXN);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			cin >> x;
			points[x].push_back({i, j});
		}
	}
	vector<vector<int>> ans(n + 1, vector<int>(m + 1));
	int X = k - 1;
	for (auto &v : points) {
		if (sz(v) == 0)
			continue;
		int ts;
		auto Add = [&](int l, int r, int v) {
			l = max(l, 0);
			r = min(r, m - 1);
			if (l > r)
				return;
			ans[ts][l] += v;
			ans[ts][r + 1] -= v;
		};
		multiset<int> s;
		auto add_point = [&](int y) {
			auto it = s.lower_bound(y);
			int LEFT = (it != s.begin() ? *prev(it) : -1e9);
			int RIGHT = (it != s.end() ? *it : 1e9);
			// cut down previous one's range
			int st = y;
			if (LEFT >= 0) {
				int appRange = min(X + 1, RIGHT - LEFT);
				st = max(st, LEFT + appRange);
			}
			// add my range
			int appRange = min(X + 1, RIGHT - y);
			Add(st, y + appRange - 1, +1);
			s.insert(y);
		};
		auto remove_point = [&](int y) {
			auto it = s.erase(s.find(y));
			int LEFT = (it != s.begin() ? *prev(it) : -1e9);
			int RIGHT = (it != s.end() ? *it : 1e9);
			int appRange = min(X + 1, RIGHT - y);
			// remove my range
			int st = y;
			if (LEFT >= 0) {
				// calculate previously excluded range, if it exists
				int appRange = min(X + 1, RIGHT - LEFT);
				st = max(st, LEFT + appRange);
			}
			Add(st, y + appRange - 1, -1);
		};
		int i = 0, j = 0;
		for (int y = k - 1; y <= n - 1; y++) {
			ts = y;
			while (i < sz(v) && v[i][0] <= y)
				add_point(v[i++][1]);
			while (j < sz(v) && v[j][0] < y - X)
				remove_point(v[j++][1]);
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i)
				ans[i][j] += ans[i - 1][j];
			if (j)
				ans[i][j] += ans[i][j - 1];
			if (i && j)
				ans[i][j] -= ans[i - 1][j - 1];
		}
	}
	lint sum = 0;
	int mx = 0;
	for (int i = k - 1; i <= n - 1; i++) {
		for (int j = k - 1; j <= m - 1; j++) {
			if (ans[i][j] > mx) {
				mx = ans[i][j];
			}
			sum += ans[i][j];
		}
	}
	cout << mx << " " << sum << "\n";
}
