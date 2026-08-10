#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

struct segtree {
	vector<int> tree;
	int lim;
	void init(vector<pi> &v) {
		if (sz(v) == 0)
			return;
		sort(all(v));
		for (lim = 1; lim <= sz(v); lim <<= 1)
			;
		cr(tree, 2 * lim + 1);
		fill(all(tree), 1e9);
		for (int i = 0; i < sz(v); i++) {
			tree[i + lim] = v[i][1];
		}
		for (int i = lim - 1; i; i--)
			tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	void eraseAt(int p) {
		p += lim;
		tree[p] = 1e9;
		while (p > 1) {
			p >>= 1;
			tree[p] = min(tree[2 * p], tree[2 * p + 1]);
		}
	}
	int query(int x) {
		if (sz(tree) == 0)
			return 1e9;
		int l = lim, r = x + lim - 1, ret = 1e9;
		while (l < r) {
			if (l % 2 == 1)
				ret = min(ret, tree[l++]);
			if (r % 2 == 0)
				ret = min(ret, tree[r--]);
			l >>= 1;
			r >>= 1;
		}
		if (l == r)
			ret = min(ret, tree[l]);
		return ret;
	}
};
vector<vector<pi>> nodes;
vector<segtree> trees;
int lim;
void initDS(int n, vector<array<int, 3>> a) {
	for (lim = 1; lim <= n; lim <<= 1)
		;
	cr(nodes, 2 * lim + 5);
	cr(trees, 2 * lim + 5);
	for (int i = 0; i < sz(a); i++) {
		for (int j = a[i][0] + lim; j; j >>= 1) {
			nodes[j].push_back({-a[i][1], i});
		}
	}
	for (int i = 0; i < sz(nodes); i++) {
		trees[i].init(nodes[i]);
	}
}

void Erase(int i, vector<array<int, 3>> &a) {
	for (int j = a[i][0] + lim; j; j >>= 1) {
		auto it = lower_bound(all(nodes[j]), pi{-a[i][1], i}) - nodes[j].begin();
		trees[j].eraseAt(it);
	}
}

int Pop(int sx, int ex, int sy) {
	if (sx > ex)
		return 1e9;
	int ll = sx + lim, rr = ex + lim, ans = 1e9;
	while (ll < rr) {
		if (ll % 2 == 1) {
			int pos = lower_bound(all(nodes[ll]), pi{-sy + 1, -1}) - nodes[ll].begin();
			ans = min(ans, trees[ll++].query(pos));
		}
		if (rr % 2 == 0) {
			int pos = lower_bound(all(nodes[rr]), pi{-sy + 1, -1}) - nodes[rr].begin();
			ans = min(ans, trees[rr--].query(pos));
		}
		ll >>= 1;
		rr >>= 1;
	}
	if (ll == rr) {
		int pos = lower_bound(all(nodes[ll]), pi{-sy + 1, -1}) - nodes[ll].begin();
		ans = min(ans, trees[ll++].query(pos));
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x - 1]++;
	}
	vector<array<int, 3>> queries(m);
	set<int> unused;
	for (int i = 0; i < m; i++) {
		cin >> queries[i][0] >> queries[i][1];
		queries[i][2] = i;
		unused.insert(i);
	}
	initDS(n, queries);
	vector<int> ans(m);
	for (int i = n - 1; i >= 0 && sz(unused); i--) {
		if (a[i] == 0)
			continue;
		auto can_fit = [&](int x) {
			x = min(x, sz(unused));
			vector<pi> v;
			auto it = unused.begin();
			for (int i = 0; i < x; i++) {
				int j = *it;
				it++;
				v.push_back({queries[j][1], queries[j][0]});
			}
			sort(all(v));
			int lst = -1e9, cnt = 0;
			for (auto &[r, l] : v) {
				if (lst < l) {
					cnt++;
					lst = r;
				}
			}
			return cnt <= a[i];
		};
		vector<pi> v;
		for (int j = 2; j <= sz(unused) * 2; j *= 2) {
			if (!can_fit(j)) {
				int s = j / 2, e = min(j, sz(unused));
				while (s != e) {
					int m = (s + e + 1) / 2;
					if (can_fit(m))
						s = m;
					else
						e = m - 1;
				}
				auto it = unused.begin();
				while (s--) {
					int j = *it;
					Erase(j, queries);
					it = unused.erase(it);
					ans[j] = i + 1;
					v.push_back({queries[j][0], queries[j][1]});
				}
				break;
			}
		}
		if (sz(v) == 0) {
			for (auto &x : unused) {
				ans[x] = i + 1;
			}
			unused.clear();
			break;
		}
		// init pareto frontiers
		set<pi> s, rs;
		auto insertPareto = [&](int l, int r) {
			auto it = s.lower_bound({l, -1});
			if (it != s.end() && (*it)[1] <= r)
				return false;
			it = s.lower_bound({l + 1, -1});
			while (it != s.begin() && (*prev(it))[1] >= r) {
				it--;
				rs.erase({-(*it)[1], -(*it)[0]});
				it = s.erase(it);
			}
			s.insert({l, r});
			rs.insert({-r, -l});
			return true;
		};
		for (auto &[l, r] : v) {
			insertPareto(l, r);
		}
		vector<pi> ends(a[i] + 1);
		for (int i = 1; i < sz(ends); i++) {
			ends[i][0] = (*s.lower_bound(pi{ends[i - 1][0] + 1, -1}))[1];
		}
		ends.back()[1] = n + 1;
		for (int i = sz(ends) - 2; i >= 0; i--) {
			ends[i][1] = -(*rs.lower_bound(pi{-ends[i + 1][1] + 1, -int(1e9)}))[1];
		}
		using node = array<int, 5>;
		priority_queue<node, vector<node>, greater<node>> pq;
		auto Enq = [&](int i) {
			int sx = (i > 0 ? (ends[i - 1][0] + 1) : 0);
			int ex = (i < sz(ends) ? ends[i][0] : n);
			int sy = (i > 0 ? ends[i - 1][1] : 0);
			//	cout << "enqueue " << i << " " << sx << " " << ex << " " << sy << endl;
			int x = Pop(sx, ex, sy);
			if (x < m)
				pq.push({x, sx, ex, sy, i});
		};
		// l0, r0 [l0, r0]
		// l1, r1 [l1, r1]
		// l2, r2 [l2, r2]
		for (int i = 0; i <= sz(ends); i++) {
			Enq(i);
		}
		while (sz(pq)) {
			auto [x, sx, ex, sy, idx] = pq.top();
			pq.pop();
			//	cout << x << endl;
			if (unused.count(x) == 0)
				continue;
			int _sx = (idx > 0 ? (ends[idx - 1][0] + 1) : 0);
			int _ex = (idx < sz(ends) ? ends[idx][0] : n);
			int _sy = (idx > 0 ? ends[idx - 1][1] : 0);
			if (sx != _sx || ex != _ex || sy != _sy) {
				continue;
			}
			//	cout << "removed " << x << endl;
			unused.erase(x);
			Erase(x, queries);
			ans[x] = i + 1;
			int l = queries[x][0], r = queries[x][1];
			set<int> todo = {idx};
			if (insertPareto(l, r)) {
				// find first ends[i][0] >= r
				// [l, r]
				int i = lower_bound(all(ends), pi{r, -int(1e9)}) - ends.begin();
				for (; i < sz(ends); i++) {
					int prv = ends[i][0];
					ends[i][0] = (*s.lower_bound({ends[i - 1][0] + 1, -1}))[1];
					if (prv != ends[i][0])
						todo.insert(i), todo.insert(i + 1);
					else
						break;
				}
				{
					int s = 0, e = sz(ends) - 1;
					while (s != e) {
						int m = (s + e + 1) / 2;
						if (ends[m][1] <= l)
							s = m;
						else
							e = m - 1;
					}
					i = s;
				}
				for (; i >= 0; i--) {
					int prv = ends[i][1];
					ends[i][1] = -(*rs.lower_bound({-ends[i + 1][1] + 1, -int(1e9)}))[1];
					if (prv != ends[i][1])
						todo.insert(i), todo.insert(i + 1);
					else
						break;
				}
			}
			for (auto &i : todo)
				Enq(i);
		}
	}
	for (auto &x : ans)
		cout << x << "\n";
}