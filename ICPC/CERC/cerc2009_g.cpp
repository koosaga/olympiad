#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int MAXT = 66666;

pi app(pi a, pi b) { return pi{min(a[0], b[0]), min(a[1], b[1])}; }
struct seg {
	pi tree[MAXT];
	int lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		fill(tree, tree + 2 * lim, pi{int(1e9), int(1e9)});
	}
	void upd(int pos, pi val) {
		pos += lim;
		tree[pos] = val;
		while (pos > 1) {
			pos >>= 1;
			tree[pos] = app(tree[2 * pos], tree[2 * pos + 1]);
		}
	}
	pi query(int s, int e) {
		s += lim;
		e += lim;
		pi ret{int(1e9), int(1e9)};
		while (s < e) {
			if (s % 2 == 1)
				ret = app(ret, tree[s++]);
			if (e % 2 == 0)
				ret = app(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = app(ret, tree[s]);
		return ret;
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n, m, d;
		cin >> n >> m >> d;
		vector<int> a(n);
		for (auto &x : a)
			cin >> x;
		m--;
		if (n % 2 == 1 || n / 2 < m) {
			cout << "BAD\n";
			continue;
		}
		auto ok = [&](int T) {
			vector<pi> dp(n / 2 + 1, pi{int(1e9), int(1e9)});
			dp[0][0] = 0;
			vector<int> L(n + 1), R(n + 1);
			int cur = 0, j = 0;
			for (int i = 0; i < n; i++) {
				while (j < n && a[j] + cur <= T)
					cur += a[j++];
				L[i] = min({2 * j - i, n, i + d * 2});
				cur -= a[i];
			}
			cur = 0, j = n;
			for (int i = n - 1; i >= 0; i--) {
				while (j && a[j - 1] + cur <= T)
					cur += a[--j];
				R[i + 1] = max({2 * j - (i + 1), 0, (i + 1) - d * 2});
				cur -= a[i];
			}
			seg.init(n / 2 + 1);
			vector<vector<int>> events(n / 2 + 1);
			for (int i = 0; i <= n; i += 2) {
				events[L[i] / 2].push_back(i);
			}
			for (int i = 2; i <= n; i += 2) {
				seg.upd(i / 2 - 1, dp[i / 2 - 1]);
				for (auto &j : events[i / 2 - 1]) {
					seg.upd(j / 2, pi{int(1e9), int(1e9)});
				}
				auto [e, o] = seg.query(R[i] / 2, n / 2);
				dp[i / 2] = {o + 1, e + 1};
			}
			return dp[n / 2][m % 2] <= m;
		};
		int l = 0, r = 1e6;
		while (l != r) {
			int mid = (l + r) / 2;
			if (ok(mid))
				r = mid;
			else
				l = mid + 1;
		}
		cout << l << "\n";
	}
}