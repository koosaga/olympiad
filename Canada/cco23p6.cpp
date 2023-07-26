#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 530000;

struct seg {
	lint tree[MAXT], lazy[MAXT];
	void lazydown(int p) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			tree[i] += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, lint v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm =(ps+pe)/2;
		add(s, e, ps, pm, 2 * p, v);
		add(s, e, pm + 1, pe, 2 * p + 1, v);
		tree[p] = max(tree[2 * p], tree[2 * p + 1]);
	}
} seg;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	lint moksum = 0, oddcnt = 0;
	for (auto &x : a)
		cin >> x, moksum += x / 2, oddcnt += x % 2;
	auto solve = [&]() {
		lint deficiency = max(0ll, seg.tree[1]);
		lint matching = oddcnt - deficiency;
		return matching + (2 * moksum - 2 * matching) / 3;
	};
	for (int i = 1; i <= n; i++) {
		seg.add(1, i, 1, n, 1, a[i - 1] % 2);
		seg.add(1, min(n, 2 * i - 1), 1, n, 1, -(a[i - 1] / 2));
	}
	while (q--) {
		int i, d;
		cin >> i >> d;
		moksum -= a[i - 1] / 2;
		oddcnt -= a[i - 1] % 2;
		seg.add(1, i, 1, n, 1, -a[i - 1] % 2);
		seg.add(1, 2 * i - 1, 1, n, 1, +(a[i - 1] / 2));
		a[i - 1] += d;
		moksum += a[i - 1] / 2;
		oddcnt += a[i - 1] % 2;
		seg.add(1, i, 1, n, 1, a[i - 1] % 2);
		seg.add(1, 2 * i - 1, 1, n, 1, -(a[i - 1] / 2));
		cout << solve() << "\n";
	}
}