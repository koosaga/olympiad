#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

pi nxt[20][500005];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, q, k;
	cin >> n >> q >> k;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	for (int i = 1; i < n; i += 2)
		a[i] *= -1;
	auto s = a;
	auto fuck = [&](lint z) {
		z %= k;
		if (z < 0)
			return z + k;
		return z;
	};
	s.insert(s.begin(), 0);
	for (int i = 1; i <= n; i++)
		s[i] += s[i - 1];
	set<pi> swp;
	for (int i = 0; i <= n; i++)
		nxt[0][i] = pi{n, (s[n] - s[i]) / k};

	for (int i = 0; i < n; i++) {
		swp.insert({fuck(s[i]), i});
		if (a[i] < 0) {
			lint r = fuck(s[i]);
			lint l = r + a[i];
			auto vacate = [&](lint L, lint R) {
				auto it = swp.lower_bound({L, -1});
				while (it != swp.end() && (*it)[0] <= R) {
					auto p = (*it)[1];
					it = swp.erase(it);
					nxt[0][p] = pi{i + 1, (s[i] - s[p]) / k};
				}
			};
			vacate(max(l + 1, 0ll), r);
			if (l < 0) {
				vacate(l + k + 1, k);
			}
		}
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j <= n; j++) {
			nxt[i][j][0] = nxt[i - 1][nxt[i - 1][j][0]][0];
			nxt[i][j][1] = nxt[i - 1][j][1] + nxt[i - 1][nxt[i - 1][j][0]][1];
		}
	}
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		lint ans = 0;
		for (int j = 19; j >= 0; j--) {
			if (nxt[j][l][0] <= r) {
				ans += nxt[j][l][1];
				l = nxt[j][l][0];
			}
		}
		ans += max(0ll, s[r] - s[l]) / k;
		cout << ans << "\n";
	}
}