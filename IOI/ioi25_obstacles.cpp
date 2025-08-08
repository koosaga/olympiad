#include "obstacles.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 530000;
const int MAXN = 200005;

vector<int> l, r;
vector<int> lp, rp;
vector<int> pmin, pmax;

struct seg {
	int tree[MAXT], lim;
	void init(vector<int> &a) {
		memset(tree, 0x3f, sizeof(tree));
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		for (int i = 0; i < sz(a); i++)
			tree[i + lim] = a[i];
		for (int i = lim - 1; i; i--)
			tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	int query(int s, int e) {
		s += lim;
		e += lim;
		int ret = 2e9;
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

pi sptl[20][MAXN], sptr[20][MAXN];
void initialize(vector<int> T, vector<int> a) {
	cr(pmin, sz(T) + 1);
	cr(pmax, sz(T) + 1);
	pmin[0] = 2e9;
	pmax[0] = -2e9;
	for (int i = 0; i < sz(T); i++) {
		pmin[i + 1] = min(pmin[i], T[i]);
		pmax[i + 1] = max(pmax[i], T[i]);
	}
	seg.init(a);
	int n = sz(a);
	cr(l, n);
	cr(r, n);
	fill(all(l), -1);
	fill(all(r), n);
	{
		vector<int> stk;
		for (int i = 0; i < n; i++) {
			while (sz(stk) && a[stk.back()] <= a[i]) {
				stk.pop_back();
			}
			if (sz(stk))
				l[i] = stk.back();
			stk.push_back(i);
		}
	}
	{
		vector<int> stk;
		for (int i = n - 1; i >= 0; i--) {
			while (sz(stk) && a[stk.back()] < a[i]) {
				stk.pop_back();
			}
			if (sz(stk))
				r[i] = stk.back();
			stk.push_back(i);
		}
	}
	cr(lp, sz(a));
	cr(rp, sz(a));
	for (int i = 0; i < sz(a); i++) {
		if (r[i] == sz(a)) {
			rp[i] = -1;
			continue;
		}
		auto pos = upper_bound(all(pmax), a[r[i]]) - pmax.begin();
		if (pos == sz(pmax)) {
			rp[i] = -1;
			continue;
		}
		int crisis = pmin[pos];
		int s = l[i], e = i;
		while (s != e) {
			int m = s + (e - s + 1) / 2;
			if (seg.query(m, r[i]) < crisis)
				s = m;
			else
				e = m - 1;
		}
		if (s == l[i]) {
			if (l[i] >= 0 && a[l[i]] <= a[r[i]]) {
				auto pos = upper_bound(all(pmax), a[l[i]]) - pmax.begin();
				int crisis = pmin[pos];
				if (seg.query(l[i] + 1, r[i] - 1) < crisis)
					rp[i] = rp[l[i]];
				else
					rp[i] = -1;
			} else
				rp[i] = -1;
		} else {
			rp[i] = s;
		}
	}
	for (int i = sz(a) - 1; i >= 0; i--) {
		if (l[i] == -1) {
			lp[i] = sz(a);
			continue;
		}
		auto pos = upper_bound(all(pmax), a[l[i]]) - pmax.begin();
		if (pos == sz(pmax)) {
			lp[i] = sz(a);
			continue;
		}

		int crisis = pmin[pos];
		int s = i, e = r[i];
		while (s != e) {
			int m = (s + e) / 2;
			if (seg.query(l[i], m) < crisis)
				e = m;
			else
				s = m + 1;
		}
		if (s == r[i]) {
			if (r[i] < sz(a) && a[l[i]] > a[r[i]]) {
				auto pos = upper_bound(all(pmax), a[r[i]]) - pmax.begin();
				int crisis = pmin[pos];
				if (seg.query(l[i] + 1, r[i] - 1) < crisis)
					lp[i] = lp[r[i]];
				else
					lp[i] = sz(a);
			} else
				lp[i] = sz(a);
		} else
			lp[i] = s;
	}
	sptl[0][0] = pi{0, 0};
	sptr[0][n + 1] = pi{n + 1, 0};
	for (int i = 0; i < n; i++) {
		sptl[0][i + 1] = pi{l[i] + 1, lp[i] + 1};
		sptr[0][i + 1] = pi{r[i] + 1, rp[i] + 1};
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j <= n + 1; j++) {
			sptl[i][j][0] = sptl[i - 1][sptl[i - 1][j][0]][0];
			sptl[i][j][1] = max(sptl[i - 1][j][1], sptl[i - 1][sptl[i - 1][j][0]][1]);
			sptr[i][j][0] = sptr[i - 1][sptr[i - 1][j][0]][0];
			sptr[i][j][1] = min(sptr[i - 1][j][1], sptr[i - 1][sptr[i - 1][j][0]][1]);
		}
	}
}

bool can_reach(int L, int R, int S, int D) {
	if (S == D)
		return true;
	if (S > D)
		swap(S, D);
	S++;
	D++;
	L++;
	R++;
	for (int i = 19; i >= 0; i--) {
		if (sptr[i][S][0] <= D) {
			if (sptr[i][S][1] < L)
				return false;
			S = sptr[i][S][0];
		}
	}
	for (int i = 19; i >= 0; i--) {
		if (sptl[i][D][0] >= S) {
			if (sptl[i][D][1] > R)
				return false;
			D = sptl[i][D][0];
		}
	}
	return true;
}
