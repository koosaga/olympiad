#include "nile.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 100005;
const int MAXT = 270000;

struct mtrx {
	lint A[3][3];
	mtrx() {
		memset(A, 0x3f, sizeof(A));
		A[0][0] = A[1][1] = A[2][2] = 0;
	}
	mtrx operator+(const mtrx &m) {
		mtrx ret;
		memset(ret.A, 0x3f, sizeof(ret.A));
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					ret.A[i][k] = min(A[i][j] + m.A[j][k], ret.A[i][k]);
				}
			}
		}
		return ret;
	}
} M[MAXN];

struct segtree {
	int lim;
	mtrx tree[MAXT];
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		for (int i = 0; i < n; i++)
			tree[i + lim] = M[i];
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
	void upd(int x, mtrx v) {
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}
} seg;

vector<long long> calculate_costs(vector<int> W, vector<int> A, vector<int> B, vector<int> E) {
	int n = sz(W);
	vector<array<lint, 3>> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = {W[i], A[i], B[i]};
	}
	sort(all(a));
	vector<array<int, 3>> events;
	for (int i = 1; i < n; i++) {
		events.push_back({int(a[i][0] - a[i - 1][0]), i - 1, i});
		if (i > 1)
			events.push_back({int(a[i][0] - a[i - 2][0]), i - 2, i});
	}
	sort(all(events));
	// d[i] = d[i-1] + a[i-1][1]
	// d[i] = d[i-2] + a[i-1][2] + a[i-2][2]
	// d[i] = d[i-3] + a[i-1][2] + a[i-3][2] + a[i-1][1]
	for (int i = 0; i < n; i++) {
		memset(M[i].A, 0x3f, sizeof(M[i].A));
		M[i].A[0][0] = a[i][1];
		M[i].A[1][0] = M[i].A[2][1] = 0;
	}
	vector<pi> ans;
	seg.init(n);
	ans.push_back({0, seg.tree[1].A[0][0]});
	for (auto &[v, l, r] : events) {
		if (r - l == 2) {
			M[l].A[0][2] = a[l][2] + a[r][2] + a[l + 1][1];
		} else {
			M[l].A[0][1] = a[l][2] + a[r][2];
		}
		seg.upd(l, M[l]);
		ans.push_back({v, seg.tree[1].A[0][0]});
	}
	vector<lint> dap(sz(E));
	vector<pi> queries;
	for (int i = 0; i < sz(E); i++) {
		queries.push_back({E[i], i});
	}
	sort(all(queries));
	int j = 0;
	for (auto &[k, idx] : queries) {
		while (j < sz(ans) && ans[j][0] <= k)
			j++;
		dap[idx] = ans[j - 1][1];
	}
	return dap;
}