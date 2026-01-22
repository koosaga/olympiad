#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 500005;

struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

int n, a[MAXN];
int cl = 1, cr = 0;
lint cur = 0;
lint cost(int l, int r) {
	while (l < cl) {
		cl--;
		cur += bit.query(a[cl] - 1);
		bit.add(a[cl], +1);
	}
	while (r > cr) {
		cr++;
		cur += bit.query(n) - bit.query(a[cr]);
		bit.add(a[cr], +1);
	}
	while (l > cl) {
		cur -= bit.query(a[cl] - 1);
		bit.add(a[cl], -1);
		cl++;
	}
	while (r < cr) {
		cur -= bit.query(n) - bit.query(a[cr]);
		bit.add(a[cr], -1);
		cr--;
	}
	return l + (n - r - 1) + cur;
}

lint f(int s, int e, int ps, int pe) {
	if (s > e)
		return 1e18;
	int m = (s + e) / 2;
	pi ans{lint(1e18), -1};
	for (int i = max(ps, m); i <= pe; i++) {
		ans = min(ans, pi{cost(m, i), i});
	}
	return min({ans[0], f(s, m - 1, ps, ans[1]), f(m + 1, e, ans[1], pe)});
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p;
		a[p - 1] = i + 1;
	}
	cout << f(0, n - 1, 0, n - 1) << "\n";
}