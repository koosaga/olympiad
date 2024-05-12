#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 270000;

struct seg {
	int tree[MAXT], lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		memset(tree, 0, sizeof(tree));
	}
	void upd(int x, int v) {
		x += lim;
		tree[x] = max(tree[x], v);
		while (x > 1) {
			x >>= 1;
			tree[x] = max(tree[2 * x], tree[2 * x + 1]);
		}
	}
	int query(int s, int e) {
		s += lim;
		e += lim;
		int ret = 0;
		while (s < e) {
			if (s % 2 == 1)
				ret = max(ret, tree[s++]);
			if (e % 2 == 0)
				ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = max(ret, tree[s]);
		return ret;
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	auto v = a;
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	auto go = [&](vector<int> a, int t) {
		seg.init(n);
		vector<int> dp(sz(a));
		for (int i = 0; i < sz(a); i++) {
			int l = upper_bound(all(v), a[i] + t) - v.begin();
			int r = lower_bound(all(v), a[i]) - v.begin();
			dp[i] = seg.query(0, l - 1) + 1;
			seg.upd(r, dp[i]);
		}
		return dp;
	};
	auto trial = [&](int t) {
		auto r = a;
		reverse(all(r));
		auto L = go(a, t);
		auto R = go(r, t);
		reverse(all(R));
		int ans = 0;
		for (int i = 0; i < n; i++)
			ans = max(ans, L[i] + R[i] - 1);
		return ans;
	};
	int s = 0, e = 1e9;
	while (s != e) {
		int mi = (s + e) / 2;
		if (trial(mi) < n - m)
			s = mi + 1;
		else
			e = mi;
	}
	cout << s << "\n";
}