#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

struct frac {
	lint a, b;
	bool operator<(const frac &x) const { return a * x.b < b * x.a; }
	bool operator<=(const frac &x) const { return a * x.b <= b * x.a; }
	bool operator==(const frac &x) const { return a * x.b == b * x.a; }
	frac operator+(const frac &f) const { return {a + f.a, b + f.b}; }
	frac operator-(const frac &f) const { return {a - f.a, b - f.b}; }
};

vector<pi> intvs;
vector<lint> sums;
vector<vector<int>> gph;
vector<frac> ans;
vector<frac> coords;
vector<vector<frac>> pushes, pops;
const int MAXT = 1050000;

struct node {
	frac left, sums;
	node operator+(const node &nd) const {
		node ret;
		ret.left = left;
		if (ret.left.b == 0)
			ret.left = nd.left;
		ret.sums = sums + nd.sums;
		return ret;
	}
} tree[MAXT];

void add(int pos, int s, int e, int p, frac v) {
	if (s == e) {
		tree[p].left = tree[p].left + v;
		tree[p].sums = tree[p].sums + v;
		return;
	}
	int m = (s + e) / 2;
	if (pos <= m)
		add(pos, s, m, 2 * p, v);
	else
		add(pos, m + 1, e, 2 * p + 1, v);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void flush(int pos, int s, int e, int p) {
	if (!tree[p].left.b)
		return;
	if (s == e) {
		tree[p].left = tree[p].sums = frac{0, 0};
		return;
	}
	int m = (s + e) / 2;
	if (pos <= m)
		flush(pos, s, m, 2 * p);
	else
		flush(pos, m + 1, e, 2 * p + 1);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

frac query(int s, int e, int p, frac v) {
	if (s == e)
		return v + tree[p].sums;
	int m = (s + e) / 2;
	if (tree[2 * p].sums + v < tree[2 * p + 1].left) {
		return query(m + 1, e, 2 * p + 1, v + tree[2 * p].sums);
	}
	return query(s, m, 2 * p, v);
}
vector<frac> qpos;
vector<int> todo;

void just_collect(int x) {
	for (int i = 0; i < sz(gph[x]); i++) {
		just_collect(gph[x][i]);
	}
	for (auto &y : pops[x]) {
		int z = lower_bound(all(coords), y) - coords.begin();
		add(300000 - z, 0, 300000, 1, frac{0, 0} - y);
		todo.push_back(z);
	}
	for (auto &y : pushes[x]) {
		int z = lower_bound(all(coords), y) - coords.begin();
		add(300000 - z, 0, 300000, 1, y);
		todo.push_back(z);
	}
}

void dfs(int x, bool clear_after_used) {
	// nothing -> nothing
	// nothing -> only subtree
	for (int i = 1; i < sz(gph[x]); i++) {
		dfs(gph[x][i], true);
	}
	if (sz(gph[x])) {
		dfs(gph[x][0], false);
	}
	for (int i = 1; i < sz(gph[x]); i++) {
		just_collect(gph[x][i]);
	}
	for (auto &y : pops[x]) {
		int z = lower_bound(all(coords), y) - coords.begin();
		add(300000 - z, 0, 300000, 1, frac{0, 0} - y);
		todo.push_back(z);
	}
	for (auto &y : pushes[x]) {
		int z = lower_bound(all(coords), y) - coords.begin();
		add(300000 - z, 0, 300000, 1, y);
		todo.push_back(z);
	}
	ans[x] = query(0, 300000, 1, qpos[x]);
	if (clear_after_used) {
		for (auto &x : todo)
			flush(300000 - x, 0, 300000, 1);
		todo.clear();
	}
}

bool cmp(pi a, pi b) { return pi{a[0], -a[1]} < pi{b[0], -b[1]}; }

void initialize(std::vector<int> a) {
	int n = sz(a);
	vector<priority_queue<frac>> pq;
	vector<int> subs;
	{
		vector<int> L(n, -1), R(n, n);
		vector<int> stk;
		for (int i = 0; i < n; i++) {
			while (sz(stk) && a[stk.back()] >= a[i])
				stk.pop_back();
			if (sz(stk))
				L[i] = stk.back();
			stk.push_back(i);
		}
		stk.clear();
		for (int i = n - 1; i >= 0; i--) {
			while (sz(stk) && a[stk.back()] >= a[i])
				stk.pop_back();
			if (sz(stk))
				R[i] = stk.back();
			stk.push_back(i);
		}
		for (int i = 0; i < n; i++) {
			if (L[i] >= 0 && R[i] < n) {
				intvs.push_back({L[i], R[i]});
			}
		}
		sort(all(intvs), cmp);
		intvs.resize(unique(all(intvs)) - intvs.begin());
		stk.clear();
		cr(gph, sz(intvs));
		cr(pq, sz(intvs));
		cr(ans, sz(intvs));
		cr(pushes, sz(intvs));
		cr(pops, sz(intvs));
		cr(subs, sz(intvs));
		cr(qpos, sz(intvs));
		for (int i = 0; i < sz(intvs); i++) {
			while (sz(stk) && intvs[stk.back()][1] < intvs[i][1])
				stk.pop_back();
			if (sz(stk)) {
				gph[stk.back()].push_back(i);
			}
			stk.push_back(i);
		}
	}
	sums.resize(n + 1);
	for (int i = 1; i <= n; i++)
		sums[i] = sums[i - 1] + a[i - 1];
	auto PUSH = [&](int v, frac f) {
		coords.push_back(f);
		pushes[v].push_back(f);
		pq[v].push(f);
	};
	auto POP = [&](int v) {
		auto tp = pq[v].top();
		pq[v].pop();
		pops[v].push_back(tp);
	};
	vector<int> roots(sz(intvs), 1);
	for (int i = sz(intvs) - 1; i >= 0; i--) {
		qpos[i] = {a[intvs[i][0]] + a[intvs[i][1]], 2};
		subs[i] = 1;
		lint cintvl = intvs[i][1] - intvs[i][0] - 1;
		lint cintvs = sums[intvs[i][1]] - sums[intvs[i][0] + 1];
		for (auto &j : gph[i]) {
			cintvl -= intvs[j][1] - intvs[j][0] - 1;
			cintvs -= sums[intvs[j][1]] - sums[intvs[j][0] + 1];
			if (sz(pq[j]) > sz(pq[i]))
				swap(pq[i], pq[j]);
			subs[i] += subs[j];
			while (sz(pq[j])) {
				auto x = pq[j].top();
				pq[i].push(x);
				pq[j].pop();
			}
			roots[j] = 0;
		}
		sort(all(gph[i]), [&](int x, int y) { return subs[x] > subs[y]; });
		assert(cintvl > 0);
		frac x = frac{cintvs, cintvl};
		while (sz(pq[i]) && x <= pq[i].top()) {
			x = x + pq[i].top();
			POP(i);
		}
		PUSH(i, x);
	}
	sort(all(coords));
	coords.resize(unique(all(coords)) - coords.begin());
	for (int i = 0; i < sz(intvs); i++) {
		if (roots[i])
			dfs(i, true);
	}
}

std::array<long long, 2> maximum_average(int i, int j) {
	if (j - i == 1) {
		return pi{sums[j + 1] - sums[i], 2};
	}
	int v = lower_bound(all(intvs), pi{i, j}, cmp) - intvs.begin();
	return pi{ans[v].a, ans[v].b};
}