#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int n, c;
vector<vector<pi>> gph;
vector<lint> dp, sz, crd;

void hld(int x) {
	sz[x] = 1;
	for (auto &[w, y] : gph[x]) {
		gph[y].erase(find(all(gph[y]), pi{w, x}));
		hld(y);
		sz[x] += sz[y];
	}
}

void pullup(vector<lint> &v, int pos, lint &install) {
	for (int i = 0; i < pos; i++)
		v[i] = 1e10;
	for (int i = pos + 1; i < sz(v); i++)
		v[i] += crd[i] - crd[pos];
	install += *min_element(all(v));
}

vector<lint> dfs(int x) {
	if (sz(gph[x]) == 0) {
		vector<lint> ans(sz(crd));
		return ans;
	}
	lint install = c * (sz(gph[x]) + (x > 0));
	auto ans = dfs(gph[x][0][1]);
	pullup(ans, gph[x][0][0], install);
	for (int i = 1; i < sz(gph[x]); i++) {
		auto nxt = dfs(gph[x][i][1]);
		pullup(nxt, gph[x][i][0], install);
		for (int i = 0; i < sz(nxt); i++)
			ans[i] += nxt[i];
	}
	for (auto &x : ans)
		x = min(x, install);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cout.tie(0);
	cin >> n >> c;
	if (n == 1) {
		cout << "0\n";
		return 0;
	}
	cr(gph, n);
	cr(dp, n);
	cr(sz, n);
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		gph[u].push_back({w, v});
		gph[v].push_back({w, u});
		crd.push_back(w);
	}
	hld(0);
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for (int i = 0; i < n; i++) {
		sort(all(gph[i]), [&](const pi &a, const pi &b) { return sz[a[1]] > sz[b[1]]; });
		for (auto &[w, j] : gph[i]) {
			w = lower_bound(all(crd), w) - crd.begin();
		}
	}
	auto ans = dfs(0);
	cout << *min_element(all(ans)) << "\n";
}