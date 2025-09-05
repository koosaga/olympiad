#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int uni(vector<pi> &v) {
	vector<pi> ev;
	for (auto &[l, r] : v) {
		ev.push_back({l, +1});
		ev.push_back({r, -1});
	}
	sort(all(ev));
	int ans = 0, cnt = 0;
	for (int i = 0; i < sz(ev) - 1; i++) {
		cnt += ev[i][1];
		if (cnt)
			ans += ev[i + 1][0] - ev[i][0];
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, sx, sy, ex, ey;
	cin >> n >> sx >> sy >> ex >> ey;
	if (sy <= ey) {
		cout << "0\n";
		return 0;
	}
	swap(sy, ey);
	vector<pi> intv;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		y1 = max(y1, sy);
		y2 = min(y2, ey);
		if (y1 < y2)
			intv.push_back({y1, y2});
	}
	cout << ey - sy - uni(intv) << "\n";
}