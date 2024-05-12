#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 1050000;

lint ccw(pi a, pi b, pi c) {
	for (int i = 0; i < 2; i++)
		b[i] -= a[i], c[i] -= a[i];
	return b[0] * c[1] - c[0] * b[1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<pi> a(n);
	for (auto &[x, y] : a) {
		cin >> x >> y;
	}
	{
		lint area = 0;
		for (int i = 2; i < n; i++) {
			area += ccw(a[0], a[i - 1], a[i]);
		}
		if (area < 0)
			reverse(all(a));
	}
	vector<array<int, 4>> v;
	for (int i = 0; i < n; i++) {
		if (a[i][0] == a[(i + 1) % n][0]) {
			int x = a[i][0];
			int l = a[i][1];
			int r = a[(i + 1) % n][1];
			if (l < r) {
				v.push_back({x, l, r, -1});
			} else {
				v.push_back({x, r, l, +1});
			}
		}
	}
	sort(all(v));
	int ans = 0;
	set<array<int, 3>> S;
	int odds = 0;
	int cnt[2] = {};
	auto INSERT = [&](array<int, 3> v) {
		if (v[0] % 2 != v[1] % 2)
			odds++;
		cnt[v[2]]++;
		S.insert(v);
	};
	auto ERASE = [&](array<int, 3> v) {
		if (v[0] % 2 != v[1] % 2)
			odds--;
		cnt[v[2]]--;
	};
	for (int i = 0; i < sz(v); i++) {
		auto [x, l, r, p] = v[i];
		if (p == -1) {
			vector<array<int, 3>> toput;
			auto it = S.lower_bound({l, -1, -1});
			if (it != S.begin() && (*prev(it))[1] > l) {
				it--;
			}
			while (it != S.end()) {
				auto [sl, sr, p] = *it;
				if (sl >= r)
					break;
				if (sl < l)
					toput.push_back({sl, l, p});
				if (r < sr)
					toput.push_back({r, sr, p});
				if (x % 2 != p) {
					cout << ans << "\n";
					return 0;
				}
				ERASE(*it);
				it = S.erase(it);
			}
			for (auto &z : toput)
				INSERT(z);
		} else {
			array<int, 3> toput = {l, r, x % 2};
			{
				auto it = S.lower_bound({r, -1, -1});
				if (it != S.end() && (*it)[0] == r && (*it)[2] == toput[2]) {
					toput[1] = (*it)[1];
					ERASE(*it);
					it = S.erase(it);
				}
			}
			{
				auto it = S.lower_bound({l, -1, -1});
				if (it != S.begin() && (*prev(it))[1] == l && (*prev(it))[2] == toput[2]) {
					it--;
					toput[0] = (*it)[0];
					ERASE(*it);
					it = S.erase(it);
				}
			}
			INSERT(toput);
		}
		if (i < sz(v) - 1 && v[i + 1][0] != v[i][0]) {
			int mask = 0;
			if (odds > 0) {
				cout << ans << "\n";
				return 0;
			}
			if (cnt[0])
				mask |= 1;
			if (cnt[1])
				mask |= 2;
			assert(mask > 0);
			if (mask == 1) {
				if (v[i + 1][0] % 2 == 0)
					ans = max(ans, v[i + 1][0]);
				else
					ans = max(ans, v[i + 1][0] - 1);
			} else if (mask == 2) {
				if (v[i + 1][0] % 2 == 1)
					ans = max(ans, v[i + 1][0]);
				else
					ans = max(ans, v[i + 1][0] - 1);
			}
		}
	}
	ans = m;
	cout << ans << "\n";
}
