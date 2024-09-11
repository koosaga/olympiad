#include "sphinx.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 256;

struct dsu {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;

vector<int> find_colours(int n, vector<int> X, vector<int> Y) {
	disj.init(n);
	vector<vector<int>> gx(n);
	for (int i = 0; i < sz(X); i++) {
		gx[Y[i]].push_back(X[i]);
	}
	auto help = [&](vector<int> rep, int c) {
		int compWithNCount = count(all(rep), c);
		dsu toCount;
		toCount.init(n);
		for (int i = 0; i < sz(X); i++) {
			if (rep[X[i]] == c && rep[Y[i]] == c) {
				compWithNCount -= toCount.uni(X[i], Y[i]);
			}
		}
		return compWithNCount;
	};
	for (int i = 0; i < n; i++) {
		map<int, int> mp;
		for (auto &j : gx[i]) {
			mp[disj.find(j)] = j;
		}
		if (sz(mp) == 0)
			continue;
		vector<int> v;
		for (auto &[x, y] : mp) {
			v.push_back(y);
		}
		auto f = [&](int l, int r) {
			vector<int> w = {i};
			for (int j = l; j < r; j++)
				w.push_back(v[j]);
			vector<int> rep(n, n);
			for (auto &x : w)
				rep[x] = -1;
			int compCount = perform_experiment(rep);
			int compWithNCount = help(rep, n);
			return compCount - compWithNCount;
		};
		for (int l = 0; l < sz(v);) {
			if (f(l, sz(v)) == sz(v) - l + 1)
				break;
			int s = l, e = sz(v);
			while (e - s > 1) {
				int m = (s + e) / 2;
				if (f(l, m) == m - l + 1)
					s = m;
				else
					e = m;
			}
			// cout << "eq " << v[s] << " " << i << endl;
			disj.uni(v[s], i);
			l = s + 1;
		}
	}
	vector<vector<int>> gph(n);
	for (int i = 0; i < sz(X); i++) {
		int u = disj.find(X[i]);
		int v = disj.find(Y[i]);
		if (u != v) {
			gph[u].push_back(v);
			gph[v].push_back(u);
		}
	}
	vector<vector<int>> cmp(n);
	for (int i = 0; i < n; i++)
		cmp[disj.find(i)].push_back(i);
	int rt = disj.find(0);
	vector<int> ord[2];
	vector<int> dep(n), vis(n);
	{
		queue<int> que;
		que.push(rt);
		vis[rt] = 1;
		while (sz(que)) {
			int x = que.front();
			que.pop();
			ord[dep[x] % 2].push_back(x);
			for (auto &y : gph[x]) {
				if (!vis[y]) {
					vis[y] = 1;
					dep[y] = dep[x] + 1;
					que.push(y);
				}
			}
		}
	}
	vector<int> ans(n, 0);
	if (sz(cmp[rt]) == n) {
		for (int i = 0; i < n; i++) {
			vector<int> rep(n, i);
			rep[0] = -1;
			if (perform_experiment(rep) == 1) {
				for (auto &j : cmp[rt])
					ans[j] = i;
				break;
			}
		}
		return ans;
	}
	for (int i = 0; i < 2; i++) {
		auto f = [&](int c, int l, int r) {
			vector<int> rep(n, c);
			for (int j = 0; j < n; j++) {
				if (sz(cmp[j]) && dep[j] % 2 == i) {
					for (auto &v : cmp[j])
						rep[v] = n;
				}
			}
			for (int j = l; j < r; j++) {
				for (auto &v : cmp[ord[i][j]])
					rep[v] = -1;
			}
			int compCount = perform_experiment(rep);
			int h1 = help(rep, c);
			int h2 = help(rep, n);
			return compCount - h1 - h2 < (r - l);
		};
		for (int j = 1; j < n; j++) {
			vector<int> used;
			for (int l = 0; l < sz(ord[i]);) {
				if (f(j, l, sz(ord[i])) == false)
					break;
				int s = l, e = sz(ord[i]);
				while (e - s > 1) {
					int m = (s + e) / 2;
					if (f(j, l, m) == false)
						s = m;
					else
						e = m;
				}
				for (auto &q : cmp[ord[i][s]])
					ans[q] = j;
				used.push_back(s);
				l = s + 1;
			}
			reverse(all(used));
			for (auto &x : used)
				ord[i].erase(ord[i].begin() + x);
		}
	}
	return ans;
}