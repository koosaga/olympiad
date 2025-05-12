#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

vector<vector<int>> tops;
vector<int> ord;
vector<int> vis;

void dfs(int x) {
	if (vis[x])
		return;
	vis[x] = 1;
	for (auto &y : tops[x]) {
		dfs(y);
	}
	ord.push_back(x);
}

struct node {
	vector<int> revs;
	int root;
};

int find(vector<int> &comp, int x) {
	if (comp[x] == x)
		return x;
	return comp[x] = find(comp, comp[x]);
}

const int MAXN = 200005;
pi edges[20][MAXN];

struct node2 {
	lint idep, cnt, weight;
	bool operator<(const node2 &nd) const { return weight > nd.weight; }
};

vector<int> in_cycle;
vector<vector<pi>> tree;
priority_queue<node2> pq[MAXN];
vector<lint> ans;

void dfs2(int x, int d = 0) {
	for (auto &[w, y] : tree[x]) {
		dfs2(y, d + 1);
		int ccnt = 0;
		while (sz(pq[y]) && pq[y].top().weight <= w) {
			ans[pq[y].top().weight] += pq[y].top().cnt * (pq[y].top().idep - d - 1);
			ccnt += pq[y].top().cnt;
			pq[y].pop();
		}
		ccnt += 1;
		pq[y].push({d + 1, ccnt, w});
		if (sz(pq[x]) < sz(pq[y])) {
			swap(pq[x], pq[y]);
		}
		while (sz(pq[y])) {
			pq[x].push(pq[y].top());
			pq[y].pop();
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	cr(tops, n);
	cr(vis, n);
	cr(ans, n);
	vector<vector<int>> gph(n);
	vector<vector<int>> rev(n);
	vector<set<int>> outs(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		gph[i].resize(x);
		for (auto &j : gph[i]) {
			cin >> j;
			j--;
		}
	}
	vector<int> dep(n);
	auto combine = [&](pi a, pi b) {
		//	cout << "comb " << a[0] << " " << a[1] << " " << b[0] << " " << b[1] << endl;
		if (dep[a[0]] > dep[b[0]])
			swap(a, b);
		lint dmax = max(a[1], b[1]);
		int dx = dep[b[0]] - dep[a[0]];
		for (int i = 0; dx; i++) {
			if (dx & 1) {
				dmax = max(dmax, edges[i][b[0]][1]);
				b[0] = edges[i][b[0]][0];
			}
			dx >>= 1;
		}
		if (b[0] == a[0])
			return pi{a[0], dmax};
		for (int i = 19; i >= 0; i--) {
			if (edges[i][a[0]][0] != edges[i][b[0]][0]) {
				dmax = max({dmax, edges[i][a[0]][1], edges[i][b[0]][1]});
				a[0] = edges[i][a[0]][0];
				b[0] = edges[i][b[0]][0];
			}
		}
		dmax = max({dmax, edges[0][a[0]][1], edges[0][b[0]][1]});
		return pi{edges[0][a[0]][0], dmax};
	};
	auto gen_relation = [&](int rt, vector<int> &comp, bool cyclic) {
		for (auto &v : comp) {
			if (v != rt) {
				for (auto &w : gph[v]) {
					tops[w].push_back(v);
				}
			}
		}
		dfs(rt);
		reverse(all(ord));
		dep[rt] = 0;
		for (int i = 0; i < 20; i++)
			edges[i][rt] = {rt, rt};
		for (auto &v : ord) {
			if (v != rt) {
				edges[0][v] = {v, -1};
				for (auto &w : gph[v]) {
					if (edges[0][v][1] == -1)
						edges[0][v] = {w, w};
					else {
						edges[0][v] = combine(edges[0][v], pi{w, w});
					}
				}
				edges[0][v][1] = max(edges[0][v][1], 1ll * v);
				dep[v] = dep[edges[0][v][0]] + 1;
				for (int i = 1; i < 20; i++) {
					edges[i][v][0] = edges[i - 1][edges[i - 1][v][0]][0];
					edges[i][v][1] = max(edges[i - 1][v][1], edges[i - 1][edges[i - 1][v][0]][1]);
				}
				// cout << v << " " << dep[v] << " " << edges[v][0] << " " << edges[v][1] << endl;
			}
		}
		if (cyclic) {
			int v = rt;
			pi curOut = {v, -1};
			for (auto &w : gph[v]) {
				if (curOut[1] == -1)
					curOut = {w, w};
				else {
					curOut = combine(curOut, pi{w, w});
				}
			}
			edges[0][v] = pi{curOut[0], max(curOut[1], 1ll * v)};
			//	cout << v << " " << dep[v] << " " << edges[v][0] << " " << edges[v][1] << endl;
		}
		for (auto &v : comp) {
			vis[v] = 0;
			tops[v].clear();
		}
		ord.clear();
	};
	cr(in_cycle, n);
	cr(tree, n);
	auto solve = [&](int rt, vector<int> &comp, bool fake_root) {
		gen_relation(rt, comp, fake_root);
		if (fake_root) {
			pi idx = pi{edges[0][rt][1], rt};
			for (int i = edges[0][rt][0]; i != rt; i = edges[0][i][0]) {
				idx = max(idx, pi{edges[0][i][1], i});
			}
			rt = idx[1];
			gen_relation(rt, comp, fake_root);
		}
		vector<int> cycles;
		for (int p = edges[0][rt][0]; p != rt; p = edges[0][p][0]) {
			cycles.push_back(p);
		}
		cycles.push_back(rt);
		for (auto &x : cycles)
			in_cycle[x] = 1;
		for (auto &v : comp) {
			if (!in_cycle[v]) {
				auto [pa, pe] = edges[0][v];
				//		cout << v << " " << pa << " " << pe << endl;
				tree[pa].push_back({pe, v});
			}
		}
		priority_queue<node2> pqcyc;
		for (int i = 0; i < sz(cycles); i++) {
			dfs2(cycles[i]);
			vector<node2> vect;
			while (sz(pq[cycles[i]])) {
				auto tp = pq[cycles[i]].top();
				pq[cycles[i]].pop();
				ans[tp.weight] += tp.idep * tp.cnt;
				vect.push_back(tp);
			}
			vect.push_back({i, 1, 0});
			lint outmax = edges[0][rt][1];
			for (auto &v : vect) {
				ans[max(outmax, v.weight)] += v.cnt * i;
				pqcyc.push({i, v.cnt, v.weight});
			}
			int w = edges[0][cycles[i]][1];
			if (i + 1 == sz(cycles))
				w = 1e9;
			int ccnt = 0;
			while (sz(pqcyc) && pqcyc.top().weight <= w) {
				ans[pqcyc.top().weight] += pqcyc.top().cnt * (i - pqcyc.top().idep);
				ccnt += pqcyc.top().cnt;
				pqcyc.pop();
			}
			pqcyc.push({i, ccnt, w});
		}
		// cout << "solved " << endl;
	};
	vector<node> roots(n);
	for (int i = 0; i < n; i++) {
		roots[i].root = i;
	}
	for (int i = 0; i < n; i++) {
		for (auto &j : gph[i]) {
			outs[i].insert(j);
			roots[j].revs.push_back(i);
		}
	}
	queue<int> que;
	for (int i = 0; i < n; i++) {
		if (sz(outs[i]) == 1) {
			que.push(i);
		}
	}
	vector<int> comps(n);
	iota(all(comps), 0);
	// outs[i] -> ds id

	while (sz(que)) {
		int x = que.front();
		que.pop();
		if (roots[find(comps, x)].root != x)
			continue;
		int y = *outs[x].begin();
		x = find(comps, x);
		assert(y == find(comps, y));
		if (y == x)
			continue;
		if (sz(roots[x].revs) > sz(roots[y].revs)) {
			swap(x, y);
			swap(roots[x].root, roots[y].root);
		}
		comps[x] = y;
		for (auto &z : roots[x].revs) {
			roots[y].revs.push_back(z);
			outs[z].erase(x);
			outs[z].insert(y);
			if (sz(outs[z]) == 1) {
				que.push(z);
			}
		}
	}
	vector<vector<int>> byComponents(n);
	for (int i = 0; i < n; i++)
		byComponents[find(comps, i)].push_back(i);
	for (int i = 0; i < n; i++) {
		if (sz(byComponents[i])) {
			int j = roots[i].root;
			solve(j, byComponents[i], sz(outs[j]) == 1);
		}
	}
	for (int i = 0; i < n; i++) {
		if (i)
			ans[i] += ans[i - 1];
		cout << ans[i] << " ";
	}
}