#include "meetings.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 2100000;

struct seg {
	pi tree[MAXT];
	int lim;
	void init(vector<pi> &seq) {
		fill(tree, tree + MAXT, pi{int(2e9), -1});
		for (lim = 1; lim <= sz(seq); lim <<= 1)
			;
		for (int i = 0; i < sz(seq); i++)
			tree[i + lim] = seq[i];
		for (int i = lim - 1; i; i--)
			tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	pi query(int s, int e) {
		s += lim;
		e += lim;
		pi ret{int(2e9), -1};
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

struct query {
	int idx;
	int st, ed;
	int x;
	lint qconst;
	bool operator<(const query &q) const { return x < q.x; }
};

struct line {
	int first;
	lint second;
};

struct chtasdf {
	vector<line> v;
	int ptr;
	void clear() {
		ptr = 0;
		v.clear();
	}
	bool bad(line a, line b, line c) { return 1.0 * (b.second - a.second) * (b.first - c.first) >= 1.0 * (c.second - b.second) * (a.first - b.first); }
	void add(int x, lint y) {
		if (v.size() > ptr && v.back().first == x) {
			if (v.back().second <= y)
				return;
			else
				v.pop_back();
		}
		while (v.size() >= ptr + 2 && bad(v[v.size() - 2], v.back(), line{x, y})) {
			v.pop_back();
		}
		v.push_back({x, y});
	}
	lint eval(int p, lint x) { return v[p].first * x + v[p].second; }
	lint query(int x) {
		if (ptr == v.size())
			return 1e18;
		while (ptr + 1 < v.size() && eval(ptr, x) >= eval(ptr + 1, x))
			ptr++;
		return eval(ptr, x);
	}
	lint query_back(int x) {
		if (ptr == v.size())
			return 1e18;
		while (sz(v) >= ptr + 2 && eval(sz(v) - 2, x) <= eval(sz(v) - 1, x))
			v.pop_back();
		return eval(sz(v) - 1, x);
	}
} cht_deq;

struct pquery {
	int x;
	lint qconst;
	int idx;
	bool mode;
};

vector<int> dfn, chn, cnt, subsz, rev;
vector<vector<pquery>> prefix_query;
vector<vector<query>> range_query;

struct segtree {
	vector<chtasdf> tree;
	int lim;
	void init(vector<pi> func) {
		for (lim = 1; lim < sz(func); lim <<= 1)
			;
		cr(tree, 2 * lim);
		for (int i = 0; i < sz(func); i++) {
			for (int j = i + lim; j; j >>= 1)
				tree[j].add(func[i][0], func[i][1]);
		}
	}
	lint query(int s, int e, int x) {
		s += lim;
		e += lim;
		lint ret = 1e18;
		while (s < e) {
			if (s % 2 == 1)
				ret = min(ret, tree[s++].query(x));
			if (e % 2 == 0)
				ret = min(ret, tree[e--].query(x));
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = min(ret, tree[s].query(x));
		return ret;
	}
} chtseg;

struct solver {
	vector<vector<int>> gph;
	vector<int> par;
	vector<pi> func;
	vector<query> queries;
	int piv;
	void dfs(int x) {
		subsz[x] = 1;
		for (auto &i : gph[x]) {
			dfs(i);
			subsz[x] += subsz[i];
		}
	}
	void hld(int x) {
		dfn[x] = piv++;
		cnt[chn[x]]++;
		rev[dfn[x]] = x;
		if (gph[x].empty())
			return;
		chn[gph[x][0]] = chn[x];
		hld(gph[x][0]);
		for (int i = 1; i < gph[x].size(); i++) {
			chn[gph[x][i]] = gph[x][i];
			hld(gph[x][i]);
		}
	}

	void solve(vector<lint> &ans) {
		int n = sz(par);
		cr(gph, n);
		cr(dfn, n);
		cr(chn, n);
		cr(cnt, n);
		cr(subsz, n);
		cr(rev, n);
		cr(range_query, n);
		cr(prefix_query, n);
		for (int i = 1; i < n; i++)
			gph[par[i]].push_back(i);
		dfs(0);
		for (int i = 0; i < n; i++) {
			sort(gph[i].begin(), gph[i].end(), [&](const int &a, const int &b) { return subsz[a] > subsz[b]; });
		}
		hld(0);
		sort(all(queries));
		for (auto &x : queries) {
			int y = x.st;
			bool droite = false;
			while (chn[y] != chn[x.ed]) {
				prefix_query[dfn[y]].push_back({x.x, x.qconst, x.idx, droite});
				droite = chn[y] > rev[dfn[par[chn[y]]] + 1];
				y = par[chn[y]];
			}
			if (dfn[x.ed] < dfn[y]) {
				range_query[chn[y]].push_back({x.idx, dfn[x.ed] + 1 - dfn[chn[y]], dfn[y] - dfn[chn[y]], x.x, x.qconst});
			}
		}
		for (int i = 0; i < n; i++) {
			if (chn[i] == i) {
				cht_deq.clear();
				vector<pi> fn;
				for (int j = dfn[i]; j < dfn[i] + cnt[i]; j++) {
					fn.push_back(func[rev[j]]);
					cht_deq.add(fn.back()[0], fn.back()[1]);
					for (auto &x : prefix_query[j]) {
						if (x.mode == 0)
							ans[x.idx] = min(ans[x.idx], cht_deq.query(x.x) + x.qconst);
					}
					reverse(all(prefix_query[j]));
					for (auto &x : prefix_query[j]) {
						if (x.mode == 1)
							ans[x.idx] = min(ans[x.idx], cht_deq.query_back(x.x) + x.qconst);
					}
				}
				if (sz(range_query[i])) {
					chtseg.init(fn);
					for (auto &x : range_query[i]) {
						ans[x.idx] = min(ans[x.idx], chtseg.query(x.st, x.ed, x.x) + x.qconst);
					}
				}
			}
		}
	}
} S1, S2;

vector<vector<int>> gph;
vector<int> a, l, r;
vector<pi> ch;
vector<lint> Lprec, Rprec; // Lprec[i] = cost for (L[i], i], Rpect[i] = cost for [i, R[i])

void dfs(int x) {
	if (~ch[x][0]) {
		dfs(ch[x][0]);
		Lprec[x] = min(Lprec[ch[x][0]] + 1ll * (x - ch[x][0] - 1) * a[ch[x][0]], Rprec[ch[x][0]] + 1ll * (ch[x][0] - l[x] - 1) * a[ch[x][0]]) + a[x];
	} else
		Lprec[x] = a[x];
	if (~ch[x][1]) {
		dfs(ch[x][1]);
		Rprec[x] = a[x] + min(Rprec[ch[x][1]] + 1ll * (ch[x][1] - x - 1) * a[ch[x][1]], Lprec[ch[x][1]] + 1ll * (r[x] - ch[x][1] - 1) * a[ch[x][1]]);
	} else
		Rprec[x] = a[x];
}

vector<long long> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
	a = H;
	int n = sz(a);
	cr(l, n);
	cr(r, n);
	cr(ch, n);
	cr(Lprec, n);
	cr(Rprec, n);
	fill(all(l), -1);
	fill(all(r), n);
	fill(all(ch), pi{-1, -1});
	cr(gph, n);
	{
		vector<int> stk;
		for (int i = 0; i < n; i++) {
			while (sz(stk) && a[stk.back()] < a[i]) {
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
			while (sz(stk) && a[stk.back()] <= a[i]) {
				stk.pop_back();
			}
			if (sz(stk))
				r[i] = stk.back();
			stk.push_back(i);
		}
		vector<pi> seq(n);
		for (int i = 0; i < n; i++)
			seq[i] = pi{-a[i], i};
		seg.init(seq);
	}
	int rt = -1;
	for (int i = 0; i < n; i++) {
		int w = i;
		if (l[i] != -1 && r[i] != n) {
			w = (a[l[i]] >= a[r[i]] ? r[i] : l[i]);
		} else if (l[i] != -1)
			w = l[i];
		else if (r[i] != n)
			w = r[i];
		if (w == i) {
			rt = i;
		} else {
			if (w < i)
				ch[w][1] = i;
			else
				ch[w][0] = i;
		}
	}
	cr(Lprec, n);
	cr(Rprec, n);
	dfs(rt);
	vector<lint> sum1(n), sum2(n);
	for (int i = n - 1; i >= 0; i--) {
		if (r[i] < n)
			sum1[i] = sum1[r[i]];
		sum1[i] += 1ll * (r[i] - i) * a[i];
	}
	for (int i = 0; i < n; i++) {
		if (l[i] >= 0)
			sum2[i] = sum2[l[i]];
		sum2[i] += 1ll * (i - l[i]) * a[i];
	}
	vector<lint> ans(sz(L), 5e18);
	S1.func.resize(n + 1);
	S1.par.resize(n + 1);
	S2.func.resize(n + 1);
	S2.par.resize(n + 1);
	S1.func[0] = S2.func[0] = pi{lint(2e9), lint(1e18)};
	for (int i = 0; i < n; i++) {
		S1.par[n - i] = n - r[i];
		S1.func[n - i] = pi{a[i], 1ll * i * a[i] + Rprec[i] + (r[i] < n ? sum1[r[i]] : 0)};
		S2.par[i + 1] = l[i] + 1;
		S2.func[i + 1] = pi{a[i], -1ll * i * a[i] + Lprec[i] + (l[i] >= 0 ? sum2[l[i]] : 0)};
	}

	for (int i = 0; i < sz(L); i++) {
		int lca = seg.query(L[i], R[i])[1];
		ans[i] = 1ll * (R[i] - L[i] + 1) * a[lca];
		if (L[i] < lca) {
			S1.queries.push_back({i, n - L[i], n - lca, -L[i], -sum1[lca] + 1ll * (1 + R[i] - lca) * a[lca]});
		}
		if (R[i] > lca) {
			S2.queries.push_back({i, R[i] + 1, lca + 1, R[i], -sum2[lca] + 1ll * (1 + lca - L[i]) * a[lca]});
		}
	}
	S1.solve(ans);
	S2.solve(ans);
	return ans;
}
