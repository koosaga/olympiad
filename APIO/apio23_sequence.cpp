#include "sequence.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 1050000;

struct node {
	int sum, pmin, pmax;
	node() { sum = pmin = pmax = 0; }
	node(int x) {
		sum = x;
		pmin = min(x, 0);
		pmax = max(x, 0);
	}
	node operator+(const node &nd) {
		node ret;
		ret.sum = sum + nd.sum;
		ret.pmin = min(pmin, sum + nd.pmin);
		ret.pmax = max(pmax, sum + nd.pmax);
		return ret;
	}
};

struct bit {
	int tree[MAXT];
	void init() { memset(tree, 0x3f, sizeof(tree)); }
	void add(int x, int v) {
		for (int i = x + 2; i < MAXT; i += i & -i)
			tree[i] = min(tree[i], v);
	}
	int query(int x) {
		int ret = 1e9;
		for (int i = x + 2; i; i -= i & -i)
			ret = min(ret, tree[i]);
		return ret;
	}
	void flush(int x) {
		for (int i = x + 2; i < MAXT; i += i & -i)
			tree[i] = 1e9;
	}
} bit;
struct seg {
	node tree[MAXT];
	int lim;
	void init(int n, int v) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		for (int i = 0; i < n; i++)
			tree[i + lim] = node(v);
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
	void upd(int x, int v) {
		x += lim;
		tree[x] = node(v);
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}
	node query(int l, int r) {
		if (l > r)
			return node();
		l += lim;
		r += lim;
		node L, R;
		while (l < r) {
			if (l % 2 == 1)
				L = L + tree[l++];
			if (r % 2 == 0)
				R = tree[r--] + R;
			l >>= 1;
			r >>= 1;
		}
		if (l == r)
			L = L + tree[l];
		return L + R;
	}
} seg;

int sequence(int n, std::vector<int> a) {
	bit.init();
	vector<vector<int>> indices(n);
	for (int i = 0; i < n; i++) {
		a[i]--;
		indices[a[i]].push_back(i);
	}
	seg.init(n, 1);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (sz(indices[i]) == 0)
			continue;
		vector<array<int, 3>> PL(sz(indices[i]) + 1), PR(sz(indices[i]) + 1);
		vector<int> vect;
		for (int j = 0; j <= sz(indices[i]); j++) {
			int l = (j ? (indices[i][j - 1]) : -1);
			int r = (j < sz(indices[i]) ? indices[i][j] : n);
			auto lsum = seg.query(0, l).sum;
			auto msum = seg.query(l + 1, r - 1);
			int sx = lsum + msum.pmin;
			int ex = lsum + msum.pmax;
			int sy = 2 * j - ex;
			int ey = 2 * j - sx;
			PL[j] = {sx, sy, j};
			PR[j] = {ex, ey, j};
			//	printf("%d %d %d %d\n", sx, sy, ex, ey);
			vect.push_back(sy);
			vect.push_back(ey);
		}

		sort(all(vect));
		for (auto &[_, y, __] : PL) {
			y = lower_bound(all(vect), y) - vect.begin();
		}
		for (auto &[_, y, __] : PR) {
			y = lower_bound(all(vect), y) - vect.begin();
		}
		sort(all(PL));
		sort(all(PR));
		int j = 0;
		for (int i = 0; i < sz(PR); i++) {
			while (j < sz(PL) && PL[j] <= PR[i]) {
				bit.add(PL[j][1], PL[j][2]);
				j++;
			}
			ans = max(ans, PR[i][2] - bit.query(PR[i][1]));
		}
		for (int k = 0; k < j; k++)
			bit.flush(PL[k][1]);
		for (auto &q : indices[i]) {
			seg.upd(q, -1);
		}
	}
	return ans;
}
