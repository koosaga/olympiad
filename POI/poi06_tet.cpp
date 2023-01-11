#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 2050;

struct seg {
	int tree[MAXT], lazy[MAXT];
	void lazydown(int p) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			lazy[i] = max(lazy[i], lazy[p]);
			tree[i] = max(tree[i], lazy[p]);
		}
	}
	void add(int s, int e, int ps, int pe, int p, int v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			tree[p] = max(tree[p], v);
			lazy[p] = max(lazy[p], v);
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2 * p, v);
		add(s, e, pm + 1, pe, 2 * p + 1, v);
		tree[p] = max(tree[2 * p], tree[2 * p + 1]);
	}
	int query(int s, int e, int ps, int pe, int p) {
		if (e < ps || pe < s)
			return 0;
		if (s <= ps && pe <= e)
			return tree[p];
		int pm = (ps + pe) / 2;
		lazydown(p);
		return max(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
	}
} T1[MAXT], T2[MAXT];

int query(int s, int e, int ps, int pe, int p, array<int, 4> todo) {
	if (e < ps || pe < s)
		return 0;
	if (s <= ps && pe <= e)
		return T1[p].query(todo[0], todo[1], todo[2], todo[3], 1);
	int pm = (ps + pe) / 2;
	int ans = max(query(s, e, ps, pm, 2 * p, todo), query(s, e, pm + 1, pe, 2 * p + 1, todo));
	ans = max(ans, T2[p].query(todo[0], todo[1], todo[2], todo[3], 1));
	return ans;
}

void upd(int s, int e, int ps, int pe, int p, array<int, 5> todo) {
	if (e < ps || pe < s)
		return;
	T1[p].add(todo[0], todo[1], todo[2], todo[3], 1, todo[4]);
	if (s <= ps && pe <= e) {
		T2[p].add(todo[0], todo[1], todo[2], todo[3], 1, todo[4]);
		return;
	}
	int pm = (ps + pe) / 2;
	upd(s, e, ps, pm, 2 * p, todo);
	upd(s, e, pm + 1, pe, 2 * p + 1, todo);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i < q; i++) {
		int sx, sy, ex, ey, h;
		cin >> ex >> ey >> h >> sx >> sy;
		ex += sx;
		ey += sy;
		int Q = query(sx, ex - 1, 0, n - 1, 1, {sy, ey - 1, 0, m - 1});
		upd(sx, ex - 1, 0, n - 1, 1, {sy, ey - 1, 0, m - 1, Q + h});
	}
	cout << T1[1].tree[1] << "\n";
}