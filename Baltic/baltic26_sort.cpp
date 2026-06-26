#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 10000000;

struct node {
	int l, r, sum;
} pool[MAXT];
int piv;

int newnode() { return ++piv; }

void init(int s, int e, int p) {
	if (s == e)
		return;
	int m = (s + e) / 2;
	pool[p].l = newnode();
	pool[p].r = newnode();
	init(s, m, pool[p].l);
	init(m + 1, e, pool[p].r);
}

void add(int pos, int s, int e, int prv, int cur) {
	pool[cur].sum = pool[prv].sum + 1;
	if (s == e)
		return;
	int m = (s + e) / 2;
	if (pos <= m) {
		pool[cur].l = newnode();
		pool[cur].r = pool[prv].r;
		add(pos, s, m, pool[prv].l, pool[cur].l);
	} else {
		pool[cur].l = pool[prv].l;
		pool[cur].r = newnode();
		add(pos, m + 1, e, pool[prv].r, pool[cur].r);
	}
}

int query(int s, int e, int ps, int pe, int p) {
	if (e < ps || pe < s)
		return 0;
	if (s <= ps && pe <= e)
		return pool[p].sum;
	int pm = (ps + pe) / 2;
	return query(s, e, ps, pm, pool[p].l) + query(s, e, pm + 1, pe, pool[p].r);
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	{
		vector<pi> inp(n);
		for (int i = 0; i < n; i++)
			cin >> inp[i][0], inp[i][1] = i;
		vector<pi> s = inp;
		sort(all(s));
		for (int i = 0; i < n; i++)
			a[i] = lower_bound(all(s), inp[i]) - s.begin();
	}
	vector<int> pa = a, sa = a;
	for (int i = 1; i < n; i++)
		pa[i] = max(pa[i], pa[i - 1]);
	for (int i = n - 2; i >= 0; i--)
		sa[i] = min(sa[i], sa[i + 1]);
	vector<int> mpos(n + 1);
	for (int i = 0; i < n; i++)
		mpos[i + 1] = mpos[i] + (a[i] != i);
	vector<int> root(n + 1);
	root[0] = newnode();
	init(0, n - 1, root[0]);
	for (int i = 1; i <= n; i++) {
		root[i] = newnode();
		add(a[i - 1], 0, n - 1, root[i - 1], root[i]);
	}
	while (q--) {
		int l, r;
		cin >> l >> r;
		if (l + r <= n) {
			bool ok = 1;
			if (mpos[n - r] != mpos[l])
				ok = 0;
			if (pa[l - 1] > sa[l])
				ok = 0;
			if (pa[n - r - 1] > sa[n - r])
				ok = 0;
			int ans = 0;
			if (mpos[l] > 0)
				ans++;
			if (mpos[n] - mpos[n - r] > 0)
				ans++;
			if (!ok)
				ans = -1;
			cout << ans << "\n";
			continue;
		}
		if (mpos[n] == 0) {
			cout << "0\n";
			continue;
		}
		if (l == n || r == n) {
			cout << "1\n";
			continue;
		}
		if (pa[l - 1] <= sa[l] && mpos[n] - mpos[l] == 0) {
			cout << "1\n";
			continue;
		}
		if (pa[n - r - 1] <= sa[n - r] && mpos[n - r] == 0) {
			cout << "1\n";
			continue;
		}
		auto sum = [&](int x1, int x2, int y1, int y2) {
			return query(y1, y2, 0, n - 1, root[x2 + 1]) - query(y1, y2, 0, n - 1, root[x1]);
		};
		auto up = [&](int x) {
			int g = l + r - n;
			return (x + g - 1) / g;
		};
		int ab = max(2 * up(sum(0, l - 1, l, n - 1)), 1 + 2 * up(sum(l, n - 1, 0, n - r - 1)));
		int ba = max(1 + 2 * up(sum(0, n - r - 1, l, n - 1)), 2 * up(sum(n - r, n - 1, 0, n - r - 1)));
		cout << max(2, min(ab, ba)) << "\n";
	}
}