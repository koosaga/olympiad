#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 33333;

struct disj {
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

vector<pi> gph[MAXN];
vector<int> dag[MAXN];
int ord1[MAXN], ord2[MAXN], vis[MAXN], piv;
int dp[MAXN];

void dfs(int x) {
	if (vis[x])
		return;
	vis[x] = 1;
	for (auto &[w, y] : gph[x]) {
		dfs(y);
	}
	ord1[x] = piv++;
}

void dfs2(int x) {
	if (!vis[x]) {
		return;
	}
	vis[x] = 0;
	for (int i = sz(gph[x]) - 1; i >= 0; i--) {
		auto [w, y] = gph[x][i];
		dfs2(y);
	}
	ord2[x] = piv++;
}

int f(int src, int snk) {
	if (src == snk)
		return 0;
	if (~dp[src])
		return dp[src];
	int ret = -1e9;
	for (auto &y : dag[src]) {
		ret = max(ret, f(y, snk) + 1);
	}
	return dp[src] = ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	int E = 0;
	for (int i = 0; i < n - 1; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int x;
			cin >> x;
			x--;
			gph[i].push_back({E, x});
			E++;
		}
	}
	dfs(0);
	piv = 0;
	dfs2(0);
	vector<pi> src(E), snk(E);
	for (int i = 0; i < n; i++) {
		for (auto &[idx, j] : gph[i]) {
			src[idx] = {ord1[j], ord2[j]};
			snk[idx] = {ord1[i], ord2[i]};
		}
	}
	sort(all(snk));
	sort(all(src));
	multiset<int> ms;
	int j = 0;
	for (int i = 0; i < sz(src); i++) {
		while (j < sz(snk) && snk[j][0] <= src[i][0]) {
			ms.insert(snk[j++][1]);
		}
		auto it = ms.upper_bound(src[i][1]);
		if (it != ms.begin()) {
			ms.erase(--it);
			E--;
		}
	}
	cout << E << "\n";
}