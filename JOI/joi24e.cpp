#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 500005;
struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;

pi spt[20][MAXN]; // 19->die
int sum[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	auto get = [&](int x, int y) { return x * m + y; };
	disj.init(n * m);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m - 1; j++) {
			if (s[j] == '1')
				disj.uni(get(i, j), get(i, j + 1));
		}
	}
	for (int i = 0; i < n - 1; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) {
			if (s[j] == '1')
				disj.uni(get(i, j), get(i + 1, j));
		}
	}
	vector<pi> intvs(n * m, pi{int(1e9), int(-1e9)});
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int c = disj.find(get(i, j));
			intvs[c][0] = min(intvs[c][0], 1ll * i);
			intvs[c][1] = max(intvs[c][1], 1ll * i);
		}
	}
	vector<int> low(n);
	iota(all(low), 0);
	for (auto &[x, y] : intvs) {
		if (x <= y) {
			low[x] = max(low[x], (int)y);
		}
	}
	for (int i = 1; i < n; i++)
		low[i] = max(low[i], low[i - 1]);
	for (int i = 1; i <= n; i++) {
		if (low[i - 1] <= i - 1)
			sum[i]++;
		sum[i] += sum[i - 1];
	}

	vector<int> nxt(n + 1, -1);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x == 1)
			nxt[i] = i;
	}
	for (int j = 1; j < n; j++) {
		nxt[j] = max(nxt[j], nxt[j - 1]);
	}
	for (int i = 0; i < n; i++) {
		spt[0][i] = pi{i, max(i, nxt[low[i]])};
	}
	for (int i = 1; i < 20; i++) {
		auto safe = [&](int j, int k) { return (int)spt[i - 1][j][k]; };
		for (int j = 0; j < n; j++) {
			spt[i][j][0] = max(safe(safe(j, 0), 1), safe(safe(j, 1), 0));
			spt[i][j][1] = safe(safe(j, 1), 1);
			int pos = safe(j, 0);
			if (~pos)
				pos = max(pos, low[pos]);
			pos = safe(pos, 0);
			spt[i][j][1] = max({spt[i][j][0], spt[i][j][1], 1ll * pos});
		}
	}
	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;
		vector<int> v;
		while (k--) {
			int a, b;
			cin >> a >> b;
			v.push_back(disj.find(get(a - 1, b - 1)));
		}
		sort(all(v));
		v.resize(unique(all(v)) - v.begin());
		if (sz(v) == 1) {
			cout << "0\n";
			continue;
		}
		vector<pi> a;
		lint l = 1e9, r = 0;
		for (auto &x : v) {
			a.push_back(intvs[x]);
			l = min(l, intvs[x][1]);
			r = max(r, intvs[x][0]);
		}
		if (l < r && sum[r] - sum[l] > 0) {
			cout << "-1\n";
			continue;
		}
		sort(all(a), [&](const pi &p, const pi &q) { return pi{p[0], -p[1]} < pi{q[0], -q[1]}; });
		{
			vector<pi> stk;
			for (auto &x : a) {
				while (sz(stk) && stk.back()[1] >= x[1])
					stk.pop_back();
				stk.push_back(x);
			}
			a = stk;
		}
		auto inside = [&](int p) {
			if (p == -1)
				return 1;
			int pos = upper_bound(all(a), pi{p, lint(1e9)}) - a.begin();
			if (pos > 0) {
				return p <= a[pos - 1][1] ? 1 : (~pos);
			}
			return (~pos);
		};
		int ans = 1;
		pi dp{-1, nxt[l]}; // max reach from cost 0, 1
		while (dp[1] < r) {
			int i0 = inside(dp[0]);
			int i1 = inside(dp[1]);
			if (i0 <= 0 && i1 <= 0) {
				lint lastHit = r;
				auto pos = ~i1;
				auto safe = [&](int i, int j, int k) {
					if (j < 0)
						return j;
					return (int)spt[i][j][k];
				};
				auto reach = [&](int x) {
					if (x == -1)
						return (int)l;
					int ans = low[x];
					return ans;
				};
				if (pos < sz(a))
					lastHit = min(lastHit, a[pos][0]);
				auto getNext = [&](pi dp, int i) {
					int a00 = safe(i, dp[0], 1), a01 = safe(i, dp[1], 0);
					int b00 = safe(i, dp[1], 1), b01 = safe(i, reach(dp[0]), 0);
					return pi{max(a00, a01), max({a00, a01, b00, b01})};
				};
				for (int i = 19; i >= 0; i--) {
					auto [p, q] = getNext(dp, i);
					if (p < lastHit && q < lastHit) {
						dp = pi{p, q};
						ans += (1 << i);
					}
				}
			}
			if (dp[1] >= r)
				break;
			pi ndp{dp[1], -1};
			auto reach = [&](int x) {
				if (x == -1)
					return l;
				lint ans = low[x];
				int pos = upper_bound(all(a), pi{x, lint(1e9)}) - a.begin();
				if (pos < sz(a))
					ans = min(ans, a[pos][1]);
				return ans;
			};
			ndp[1] = max(1ll * nxt[reach(dp[1])], reach(dp[0]));
			ndp[1] = max(ndp[1], ndp[0]);
			ans++;
			dp = ndp;
		}

		cout << ans << "\n";
	}
}