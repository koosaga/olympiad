#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 530000;

struct node {
	lint cnt, sum, lz;
	node operator+(const node &nd) const { return (node){cnt + nd.cnt, sum + nd.sum, 0}; }
};

struct seg {
	node tree[MAXT];
	void lazydown(int p) {
		if (tree[p].lz) {
			for (int i = 2 * p; i < 2 * p + 2; i++) {
				tree[i].lz += tree[p].lz;
				tree[i].sum += tree[p].lz * tree[i].cnt;
			}
			tree[p].lz = 0;
		}
	}
	void upd(int pos, int s, int e, int p, int v) {
		if (s == e) {
			tree[p].cnt += v;
			return;
		}
		lazydown(p);
		int m = (s + e) / 2;
		if (pos <= m)
			upd(pos, s, m, 2 * p, v);
		else
			upd(pos, m + 1, e, 2 * p + 1, v);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
	lint query(int s, int e, int ps, int pe, int p) {
		if (e < ps || pe < s)
			return 0;
		if (s <= ps && pe <= e)
			return tree[p].sum;
		lazydown(p);
		int pm = (ps + pe) / 2;
		return query(s, e, ps, pm, 2 * p) + query(s, e, pm + 1, pe, 2 * p + 1);
	}
	void rupd(int s, int e, int ps, int pe, int p) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			tree[p].sum += tree[p].cnt;
			tree[p].lz += 1;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		rupd(s, e, ps, pm, 2 * p);
		rupd(s, e, pm + 1, pe, 2 * p + 1);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
} seg;

vector<long long> maxsum(vector<int> A, vector<int> B, vector<int> L1, vector<int> R1, vector<int> L2, vector<int> R2) {
	int n = sz(A);
	vector<int> okL(n + 1), okR(n + 1);
	okL[0] = okR[n] = 1;
	{
		lint sum = 0, minsum = 0;
		for (int i = 0; i < n; i++) {
			sum += A[i];
			if (minsum >= sum) {
				minsum = sum;
				okL[i + 1] = 1;
			}
		}
		sum = 0, minsum = 0;
		for (int i = n - 1; i >= 0; i--) {
			sum += A[i];
			if (minsum >= sum) {
				minsum = sum;
				okR[i] = 1;
			}
		}
	}
	vector<int> f3(n + 1), f4(n + 1), f5(n + 1), f6(n + 1);
	{
		lint maxsum = -1e18, cur = -1e18;
		for (auto &x : A) {
			cur = max(cur, 0ll) + x;
			maxsum = max(maxsum, cur);
		}
		vector<lint> sum(n + 1);
		for (int i = 0; i < n; i++) {
			sum[i + 1] = sum[i] + B[i];
		}
		vector<int> stk = {-1};
		for (int i = 0; i <= n; i++) {
			auto pred1 = [&](int j) {
				if (j == -1)
					return true;
				return sum[i] < sum[j];
			};
			int s = 0, e = sz(stk);
			while (s != e) {
				int m = (s + e) / 2;
				if (pred1(stk[m]))
					s = m + 1;
				else
					e = m;
			}
			f4[i] = stk[s - 1];
			while (sz(stk) > 1 && sum[stk.back()] <= sum[i])
				stk.pop_back();

			stk.push_back(i);
		}
		stk.clear();
		stk.push_back(-1);
		for (int i = 0; i <= n; i++) {
			auto pred2 = [&](int j) {
				if (j == -1)
					return true;
				return sum[i] - sum[j] >= maxsum;
			};
			int s = 0, e = sz(stk);
			while (s != e) {
				int m = (s + e) / 2;
				if (pred2(stk[m]))
					s = m + 1;
				else
					e = m;
			}
			f6[i] = stk[s - 1];
			while (sz(stk) > 1 && sum[stk.back()] >= sum[i])
				stk.pop_back();

			stk.push_back(i);
		}
		stk.clear();
		stk.push_back(n + 1);
		for (int i = n; i >= 0; i--) {
			auto pred1 = [&](int j) {
				if (j == n + 1)
					return true;
				return sum[j] - sum[i] < 0;
			};
			int s = 0, e = sz(stk);
			while (s != e) {
				int m = (s + e) / 2;
				if (pred1(stk[m]))
					s = m + 1;
				else
					e = m;
			}
			f3[i] = stk[s - 1];
			while (sz(stk) > 1 && sum[stk.back()] >= sum[i])
				stk.pop_back();

			stk.push_back(i);
		}
		stk.clear();
		stk.push_back(n + 1);
		for (int i = n; i >= 0; i--) {
			auto pred2 = [&](int j) {
				if (j == n + 1)
					return true;
				return sum[j] - sum[i] >= maxsum;
			};
			int s = 0, e = sz(stk);
			while (s != e) {
				int m = (s + e) / 2;
				if (pred2(stk[m]))
					s = m + 1;
				else
					e = m;
			}
			f5[i] = stk[s - 1];
			while (sz(stk) > 1 && sum[stk.back()] <= sum[i])
				stk.pop_back();

			stk.push_back(i);
		}
	}
	vector<vector<array<int, 2>>> upd(n + 2);
	for (int i = 0; i <= n; i++) {
		if (okR[i]) {
			int l = max(f4[i], 0);
			int r = min(f6[i], n) + 1;
			if (l < r) {
				upd[l].push_back({i, +1});
				upd[r].push_back({i, -1});
			}
		}
	}
	vector<vector<array<int, 4>>> qry(n + 1);
	for (int i = 0; i < sz(L1); i++) {
		qry[R1[i]].push_back({+1, i, L2[i] + 1, R2[i] + 1});
		if (L1[i])
			qry[L1[i] - 1].push_back({-1, i, L2[i] + 1, R2[i] + 1});
	}
	vector<lint> ans(sz(L1));
	{
		vector<int> ds(n + 1), on(n + 1);
		for (int i = 0; i <= n; i++) {
			for (auto &[k, v] : upd[i])
				seg.upd(k, 0, n, 1, v);
			if (okL[i])
				seg.rupd(max(f5[i], 0), min(n, f3[i]), 0, n, 1);
			for (auto &[b, idx, l, r] : qry[i]) {
				ans[idx] += b * seg.query(l, r, 0, n, 1);
			}
		}
	}
	return ans;
}