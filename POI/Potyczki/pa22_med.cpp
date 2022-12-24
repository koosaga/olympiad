#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

const int MAXN = 1005;

vector<int> inrec, ans;
set<int> s[MAXN];
set<int> active;
int opt;

int pa[MAXN], edges[MAXN], hasCycle[MAXN];
vector<int> cond[MAXN];
int penalty[MAXN];

int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
bool uni(int p, int q) {
	p = find(p);
	q = find(q);
	if (p == q) {
		hasCycle[p] = 1;
		edges[p]++;
		return 0;
	}
	pa[q] = p;
	edges[p] += edges[q] + 1;
	hasCycle[p] |= hasCycle[q];
	return 1;
}

bool oddPath(int v) {
	v = find(v);
	return !hasCycle[v] && edges[v] % 2 == 0;
}

void colorBadPath(int x, int p, int d) {
	if (d % 2 == 0)
		penalty[x] = 1;
	for (auto &y : cond[x]) {
		if (y != p)
			colorBadPath(y, x, d + 1);
	}
}

void dfs() {
	if (sz(inrec) > opt)
		return;
	if (sz(active) == 0) {
		for (auto &x : inrec)
			ans[x] = min(ans[x], sz(inrec));
		opt = sz(inrec);
		return;
	}
	pi foo{-1557, -1};
	for (auto &x : active) {
		foo = max(foo, pi{sz(s[x]), x});
	}
	int v = foo[1];
	int D = foo[0];
	if (D == 1) {
		int toUpd = sz(inrec) + sz(active) / 2;
		for (auto &x : inrec)
			ans[x] = min(ans[x], toUpd);
		for (auto &x : active)
			ans[x] = min(ans[x], toUpd);
		return;
	}
	if (D == 2) {
		for (auto &x : active) {
			pa[x] = x;
		}
		for (auto &x : active) {
			for (auto &y : s[x]) {
				if (x < y)
					uni(x, y);
			}
		}
		int toUpd = sz(inrec);
		for (auto &x : active) {
			if (find(x) == x)
				toUpd += (edges[x] + 1) / 2;
			if (oddPath(x)) {
				for (auto &y : s[x]) {
					cond[x].push_back(y);
				}
			}
		}
		for (auto &i : active) {
			if (sz(cond[i]) == 1) {
				colorBadPath(i, -1, 0);
			}
		}
		for (auto &x : inrec) {
			ans[x] = min(ans[x], toUpd);
		}
		for (auto &x : active) {
			ans[x] = min(ans[x], toUpd + penalty[x]);
		}
		for (auto &i : active) {
			cond[i].clear();
			penalty[i] = 0;
			pa[i] = hasCycle[i] = edges[i] = 0;
		}
		return;
	}
	auto insEdg = [&](int u, int v) {
		if (sz(s[u]) == 0)
			active.insert(u);
		if (sz(s[v]) == 0)
			active.insert(v);
		s[u].insert(v);
		s[v].insert(u);
	};
	auto delEdg = [&](int u, int v) {
		s[u].erase(v);
		s[v].erase(u);
		if (sz(s[u]) == 0)
			active.erase(u);
		if (sz(s[v]) == 0)
			active.erase(v);
	};
	vector<int> stk;
	for (auto &x : s[v])
		stk.push_back(x);
	for (auto &x : stk)
		delEdg(v, x);
	inrec.push_back(v);
	dfs();
	inrec.pop_back();
	vector<pi> whoDel;
	for (auto &y : stk) {
		vector<int> stk2;
		for (auto &z : s[y])
			stk2.push_back(z);
		for (auto &z : stk2)
			delEdg(y, z), whoDel.push_back({y, z});
		inrec.push_back(y);
	}
	dfs();
	for (auto &[y, z] : whoDel)
		insEdg(y, z);
	for (auto &x : stk) {
		insEdg(v, x);
		inrec.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int t;
	cin >> t;
	while (t--) {
		int n, m, k;
		cin >> n >> m >> k;
		vector<vector<int>> gph(n);
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			gph[u].push_back(v);
			gph[v].push_back(u);
		}
		for (int i = 0; i < n; i++) {
			sort(all(gph[i]));
			gph[i].resize(unique(all(gph[i])) - gph[i].begin());
		}
		vector<int> fix;
		for (int i = 0; i < k + 1; i++) {
			for (int j = 0; j < n; j++) {
				if (sz(gph[j]) > k - i) {
					fix.push_back(j);
					for (auto &k : gph[j]) {
						gph[k].erase(find(all(gph[k]), j));
					}
					gph[j].clear();
					break;
				}
			}
			if (sz(fix) < i + 1)
				break;
		}
		if (sz(fix) > k) {
			cout << "-1\n";
			continue;
		}
		sort(all(fix));
		int sum = 0;
		active.clear();
		for (int x = 0; x < n; x++) {
			sum += sz(gph[x]);
			s[x].clear();
			if (sz(gph[x])) {
				active.insert(x);
				for (auto &y : gph[x])
					s[x].insert(y);
			}
		}
		if (sum / 2 > (k - sz(fix)) * (k - sz(fix))) {
			cout << "-1\n";
			continue;
		}
		ans.resize(n);
		fill(all(ans), k + 1);
		opt = k + 1;
		inrec = fix;
		dfs();
		int minv = *min_element(all(ans));
		if (minv == k + 1) {
			cout << "-1\n";
			continue;
		}
		for (auto &x : fix)
			ans[x] = minv;
		int cnt = count(all(ans), minv);
		cout << minv << " " << cnt << "\n";
		for (int i = 0; i < n; i++) {
			if (ans[i] == minv)
				cout << i + 1 << " ";
		}
		cout << "\n";
	}
}