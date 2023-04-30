#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 270000;

struct seg {
	lint tree[MAXT];
	int lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		memset(tree, 0x3f, sizeof(tree));
	}
	void upd(int x, lint v) {
		x += lim;
		tree[x] = min(tree[x], v);
		while (x > 1) {
			x >>= 1;
			tree[x] = min(tree[2 * x], tree[2 * x + 1]);
		}
	}
	lint query(int s, int e) {
		s += lim;
		e += lim;
		lint ret = 3e18;
		while (s < e) {
			if (s % 2 == 1)
				ret = min(ret, tree[s++]);
			if (e % 2 == 0)
				ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = min(ret, tree[s]);
		return ret;
	}
} seg;
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint b, p, d, n;
	cin >> b >> p >> d >> n;
	vector<lint> a(n + 1);
	vector<lint> dp(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	vector<lint> crd;
	for (int i = 0; i <= n; i++) {
		crd.push_back(a[i] % p);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	seg.init(sz(crd));
	for (int i = 1; i <= n; i++) {
		int upos = lower_bound(all(crd), a[i - 1] % p) - crd.begin();
		seg.upd(upos, dp[i - 1] + (-(a[i - 1] / p)) * (p + d));
		int qpos = lower_bound(all(crd), a[i] % p) - crd.begin();
		dp[i] = min(seg.query(0, qpos - 1) + (p + d), seg.query(qpos, sz(crd) - 1));
		dp[i] += (p + d) * (a[i] / p) - d;
	}
	lint ans = 3e18;
	for (int i = 0; i <= n; i++) {
		lint per = (b - a[i] + p - 1) / p;
		ans = min(ans, dp[i] + (per - 1) * d + b - a[i]);
	}
	cout << ans << "\n";
}