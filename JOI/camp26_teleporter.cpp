#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
const int MAXN = 400050;
const int MAXC = 400005;
typedef pair<lint, lint> pi;

struct intv {
	lint s, e, x;
} a[MAXN];

int n, k;
pi dp[MAXN];

struct seg {
	pi tree[1050000];
	int lim;
	lint lazy[1050000];
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		memset(lazy, 0, sizeof(lazy));
		fill(tree, tree + 1050000, pi(1e18, 1e18));
	}
	void update(int e, lint x) {
		int s = lim;
		e += lim;
		while (s < e) {
			if (e % 2 == 0) {
				lazy[e] += x;
				tree[e].first += x;
			}
			if (e + 1 < lim) {
				tree[e + 1] = min(tree[2 * e + 2], tree[2 * e + 3]);
				tree[e + 1].first += lazy[e + 1];
			}
			e--;
			s >>= 1;
			e >>= 1;
		}
		if (s == e) {
			lazy[e] += x;
			tree[e].first += x;
			if (e + 1 < lim) {
				tree[e + 1] = min(tree[2 * e + 2], tree[2 * e + 3]);
				tree[e + 1].first += lazy[e + 1];
			}
		}
		while (e > 1) {
			e >>= 1;
			tree[e] = min(tree[2 * e], tree[2 * e + 1]);
			tree[e].first += lazy[e];
		}
	}
	void update(int x, pi v) {
		x += lim;
		for (int j = x / 2; j; j >>= 1)
			v.first -= lazy[j];
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = min(tree[2 * x], tree[2 * x + 1]);
			tree[x].first += lazy[x];
		}
	}
	pi query() { return tree[1]; }
} seg;

pi trial(lint x) {
	int p = 0;
	dp[0] = pi(0, 0);
	seg.init(MAXC);
	seg.update(0, dp[0]);
	for (int i = 1; i <= MAXC; i++) {
		while (p < n && a[p].e <= i) {
			seg.update(a[p].s - 1, a[p].x);
			p++;
		}
		dp[i] = seg.query();
		dp[i].first += x;
		dp[i].second++;
		seg.update(i, dp[i]);
	}
	return dp[MAXC];
}

int main() {
	scanf("%*d %d %d", &n, &k);
	int sum = 0;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &a[i].s, &a[i].e, &a[i].x);
		a[i].s *= 2;
		a[i].e *= 2;
		a[i].s++;
		sum += a[i].x;
		v.push_back(a[i].s);
		v.push_back(a[i].e);
	}
	v.push_back(-2.1e9);
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for (int i = 0; i < n; i++) {
		a[i].s = lower_bound(all(v), a[i].s) - v.begin();
		a[i].e = lower_bound(all(v), a[i].e) - v.begin();
	}
	sort(a, a + n, [&](const intv &p, const intv &q) { return p.e < q.e; });
	lint s = 0, e = 5e13;
	while (s != e) {
		lint m = (s + e) / 2;
		if (trial(m).second <= k + 1)
			e = m;
		else
			s = m + 1;
	}
	cout << (trial(s).first - 1ll * (k + 1) * s);
}
