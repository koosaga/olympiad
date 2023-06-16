#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;
const int mod = 1e9 + 7; // 993244853;

struct disj {
	int pa[MAXN];
	vector<int> elems[MAXN];
	void init(int n) {
		for (int i = 0; i < n; i++) {
			pa[i] = i;
			elems[i].clear();
			elems[i].push_back(i);
		}
	}
	int find(int x) { return pa[x] == x ? x : find(pa[x]); }
} disj;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, s[2];
	lint k;
	cin >> n >> s[0] >> s[1] >> k;
	if (k == 0) {
		cout << "0\n";
		return 0;
	}
	vector<array<int, 3>> edg[2];
	vector<array<lint, 4>> relabel[2]; // (weight, pos, prv, cur)
	vector<pi> starts(n);
	for (int i = 0; i < n; i++)
		starts[i][0] = i;
	for (int i = 0; i < 2; i++) {
		edg[i].resize(s[i]);
		for (auto &[w, u, v] : edg[i]) {
			cin >> u >> v >> w;
			u--;
			v--;
		}
		sort(all(edg[i]));
		disj.init(n);
		vector<array<int, 3>> spans;
		vector<pi> punk;
		auto Go = [&](int w, int u, int v, int iu, int iv) {
			spans.push_back({w, u, v});
			if (sz(disj.elems[iu]) > sz(disj.elems[iv]))
				swap(iu, iv);
			disj.pa[iu] = iv;
			for (auto x : disj.elems[iu]) {
				relabel[i].push_back({w, x, iu, iv});
				disj.elems[iv].push_back(x);
			}
		};
		for (auto [w, u, v] : edg[i]) {
			int iu = disj.find(u);
			int iv = disj.find(v);
			if (iu == iv)
				continue;
			Go(w, u, v, iu, iv);
		}
		for (int v = 1; v < n; v++) {
			int u = 0, w = 2.001e9;
			int iu = disj.find(u);
			int iv = disj.find(v);
			if (iu == iv)
				continue;
			Go(w, u, v, iu, iv);
		}
		if (i == 1) {
			for (int j = 0; j < n; j++)
				starts[j][1] = disj.find(0);
		}
	}
	vector<int> c1(n), c2(n);
	map<pi, int> cnt;
	lint c1isec = 0, c2isec = 0, cntisec = 0;
	for (auto &x : starts) {
		c1[x[0]]++;
		c2[x[1]]++;
		cnt[x]++;
	}
	c2isec = 1ll * n * (n - 1) / 2;
	auto update = [&](pi x, pi y) {
		c1[x[0]]--;
		c2[x[1]]--;
		cnt[x]--;
		c1isec -= c1[x[0]];
		c2isec -= c2[x[1]];
		cntisec -= cnt[x];
		c1isec += c1[y[0]];
		c2isec += c2[y[1]];
		cntisec += cnt[y];
		c1[y[0]]++;
		c2[y[1]]++;
		cnt[y]++;
	};
	auto query = [&]() { return c1isec + c2isec - cntisec; };
	int ptr = sz(relabel[1]);
	lint ans = 1e10;
	while (ptr > 0 && query() >= k) {
		ans = min(ans, relabel[1][ptr - 1][0]);
		int nxt = ptr;
		while (nxt > 0 && relabel[1][nxt - 1][0] == relabel[1][ptr - 1][0]) {
			auto [_, pos, prv, cur] = relabel[1][--nxt];
			pi upd = {starts[pos][0], (int)prv};
			update(starts[pos], upd);
			starts[pos] = upd;
		}
		ptr = nxt;
	}
	for (int i = 0; i < sz(relabel[0]);) {
		int j = i;
		while (j < sz(relabel[0]) && relabel[0][i][0] == relabel[0][j][0])
			j++;
		for (int k = i; k < j; k++) {
			auto [_, pos, prv, cur] = relabel[0][k];
			pi nxt = {(int)cur, starts[pos][1]};
			update(starts[pos], nxt);
			starts[pos] = nxt;
		}
		while (query() >= k) {
			if (ptr == 0) {
				ans = min(ans, relabel[0][i][0]);
				break;
			}
			ans = min(ans, relabel[0][i][0] + relabel[1][ptr - 1][0]);
			int nxt = ptr;
			while (nxt > 0 && relabel[1][nxt - 1][0] == relabel[1][ptr - 1][0]) {
				auto [_, pos, prv, cur] = relabel[1][--nxt];
				pi upd = {starts[pos][0], (int)prv};
				update(starts[pos], upd);
				starts[pos] = upd;
			}
			ptr = nxt;
		}
		i = j;
	}
	if (ans > 2e9 + 1557)
		ans = -1;
	cout << ans << "\n";
}
