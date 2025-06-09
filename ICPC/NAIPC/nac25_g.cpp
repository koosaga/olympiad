#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

struct treeDecomp {
	bool valid;
	vector<int> par;
	vector<vector<int>> bags;
};

vector<int> gph[MAXN];
vector<int> bags[MAXN];
vector<int> ord;

void dfs(int x) {
	for (auto &y : gph[x]) {
		dfs(y);
	}
	ord.push_back(x);
}

map<pi, lint> mp;

// Tree decomposition, width 2
treeDecomp tree_decomposition(int n, vector<pi> edges) {
	vector<set<int>> gph(n);
	for (auto &[u, v] : edges) {
		gph[u].insert(v);
		gph[v].insert(u);
	}
	treeDecomp ret;
	ret.valid = false;
	ret.par.resize(n, -1);
	ret.bags.resize(n);
	queue<int> que;
	for (int i = 0; i < n; i++) {
		if (sz(gph[i]) <= 2)
			que.push(i);
	}
	auto rem_edge = [&](int u, int v) {
		gph[u].erase(gph[u].find(v));
		gph[v].erase(gph[v].find(u));
	};
	vector<array<int, 2>> pcand(n, pi{-1, -1});
	vector<int> ord(n, -1);
	int piv = 0;
	while (sz(que)) {
		int x = que.front();
		que.pop();
		if (ord[x] != -1)
			continue;
		ret.bags[x].push_back(x);
		ord[x] = piv++;
		if (sz(gph[x]) == 1) {
			int y = *gph[x].begin();
			rem_edge(x, y);
			ret.bags[x].push_back(y);
			if (sz(gph[y]) <= 2)
				que.push(y);
			pcand[x] = pi{y, y};
		}
		if (sz(gph[x]) == 2) {
			int u = *gph[x].begin();
			int v = *gph[x].rbegin();
			rem_edge(x, u);
			rem_edge(x, v);
			gph[u].insert(v);
			gph[v].insert(u);
			ret.bags[x].push_back(u);
			ret.bags[x].push_back(v);
			if (sz(gph[u]) <= 2)
				que.push(u);
			if (sz(gph[v]) <= 2)
				que.push(v);
			pcand[x] = pi{u, v};
		}
	}
	if (piv != n)
		return ret;
	ret.valid = true;
	int root = -1;
	for (int i = 0; i < n; i++) {
		if (pcand[i][0] == -1) {
			if (root != -1)
				ret.par[i] = root;
			else
				root = i;
			continue;
		}
		if (ord[pcand[i][0]] < ord[pcand[i][1]])
			swap(pcand[i][0], pcand[i][1]);
		ret.par[i] = pcand[i][1];
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<pi> edges;
	lint dap = -1e18;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		edges.push_back({u, v});
		if (mp.count(pi{u, v})) {
			dap = max(dap, w + mp[pi{u, v}]);
			w = max(w, (int)mp[pi{u, v}]);
		}
		mp[pi{u, v}] = mp[pi{v, u}] = w;
	}
	auto td = tree_decomposition(n, edges);
	assert(td.valid);
	int rt = -1;
	for (int i = 0; i < n; i++) {
		if (td.par[i] != -1)
			gph[td.par[i]].push_back(i);
		else
			rt = i;
	}
	for (int i = 0; i < n; i++) {
		bags[i] = td.bags[i];
		for (auto &j : bags[i]) {
			for (auto &k : bags[i]) {
				if (j != k && !mp.count(pi{j, k}))
					mp[pi{j, k}] = -lint(1e18);
			}
		}
	}
	dfs(rt);
	for (auto &x : ord) { /*
		 for (auto &z : bags[x])
			 cout << z << " ";
		 cout << x << endl;*/
		if (sz(bags[x]) >= 3) {
			int u = bags[x][0];
			int v = bags[x][1];
			int w = bags[x][2];
			lint opt1 = mp[pi{u, v}];
			lint opt2 = mp[pi{u, w}];
			dap = max(dap, mp[pi{w, v}] + opt1 + opt2);
			lint foo = max(opt1 + opt2, mp[pi{w, v}]);
			mp[pi{w, v}] = mp[pi{v, w}] = foo;
		}
	}
	cout << dap << "\n";
}
