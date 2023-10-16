#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

vector<pi> gph[MAXN];
vector<int> dfn;
int sz[MAXN], msz[MAXN], vis[MAXN], par[MAXN];

void dfs(int x, int p = -1) {
	dfn.push_back(x);
	sz[x] = 1, msz[x] = 0;
	for (auto &y : gph[x]) {
		if (y[1] != p && !vis[y[1]]) {
			dfs(y[1], x);
			sz[x] += sz[y[1]];
			msz[x] = max(msz[x], sz[y[1]]);
		}
	}
}

int get_center(int x) {
	dfn.clear();
	dfs(x);
	pi ret{int(1e9), -1};
	for (auto &x : dfn) {
		int w = max(sz(dfn) - sz[x], msz[x]);
		ret = min(ret, pi{w, x});
	}
	return ret[1];
}

struct query {
	int u, v, a, b, idx;
};

pi dp[MAXN], pdp[MAXN];
vector<pi> far[MAXN];

void dfs_far(int x, int p) {
	dp[x] = {0, x};
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			dfs_far(y, x);
			dp[x] = max(dp[x], pi{dp[y][0] + w, dp[y][1]});
			far[x].push_back(pi{dp[y][0] + w, y});
		}
	}
}

void dfs_spread(int x, int p) {
	if (p != -1) {
		far[x].push_back(pdp[x]);
	}
	far[x].push_back({0, x});
	sort(all(far[x]));
	reverse(all(far[x]));
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			for (int k = 0; k < 3 && k < sz(far[x]); k++) {
				if (far[x][k][1] != y) {
					pdp[y] = pi{far[x][k][0] + w, x};
					break;
				}
			}
			dfs_spread(y, x);
		}
	}
}

lint far_avoid(int x, vector<int> to_avoid) {
	for (auto &[dist, frm] : far[x]) {
		if (count(all(to_avoid), frm) == 0) {
			return dist;
		}
	}
	return 0;
}

lint T1[MAXN], GEN[MAXN], DK[MAXN];
lint F1[MAXN], F2[MAXN];

int lab[MAXN], dep[MAXN];
vector<int> ord;
vector<array<lint, 4>> upload[MAXN]; // A, B, store, added value

void dfs2(int x, int p, int l) {
	lab[x] = l;
	par[x] = p;
	T1[x] = far_avoid(x, {par[x]});
	if (lab[p] != -1) {
		GEN[x] = far_avoid(par[x], {x, par[par[x]]});
		DK[x] = max(DK[x], GEN[x] + dep[par[x]]);
		F1[x] = F2[x] = GEN[x] - dep[par[x]];
	} else
		F1[x] = F2[x] = -1e9;
	ord.push_back(x);
	for (auto &[w, y] : gph[x]) {
		if (y != p && !vis[y]) {
			DK[y] = DK[x];
			dep[y] = dep[x] + w;
			dfs2(y, x, l);
		}
	}
}

lint ccw(pi a, pi b, pi c) {
	for (int i = 0; i < 2; i++)
		b[i] -= a[i], c[i] -= a[i];
	return b[0] * c[1] - c[0] * b[1];
}

pi points[MAXN];
int hsz;
void dfs_query(int x, int p, vector<lint> &ans) {
	int psz = -1;
	pi pbef = pi{-1, -1};
	int pbefloc = -1;
	if (lab[par[x]] != -1) {
		pi nxt = {DK[par[x]], F1[x]};
		if (hsz && points[hsz - 1][0] == nxt[0] && points[hsz - 1][1] >= nxt[1]) {
		} else {
			int s = 0, e = hsz - 1;
			if (s > e)
				s--;
			while (s < e) {
				int m = (s + e) / 2;
				if (ccw(points[m], points[m + 1], nxt) >= 0)
					e = m;
				else
					s = m + 1;
			}
			psz = hsz;
			pbef = points[s + 1];
			pbefloc = s + 1;

			points[s + 1] = nxt;
			hsz = s + 2;
		}
	}
	if (hsz) {
		for (auto &[a, b, idx, off] : upload[x]) {
			int s = 0, e = hsz - 1;
			while (s != e) {
				int m = (s + e) / 2;
				if (a * points[m][0] + b * points[m][1] < a * points[m + 1][0] + b * points[m + 1][1])
					s = m + 1;
				else
					e = m;
			}
			ans[idx] = max(ans[idx], a * points[s][0] + b * points[s][1] + off);
		}
	}
	for (auto &[w, y] : gph[x]) {
		if (y != p && !vis[y]) {
			dfs_query(y, x, ans);
		}
	}
	if (psz != -1) {
		hsz = psz;
		points[pbefloc] = pbef;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		gph[u].push_back({w, v});
		gph[v].push_back({w, u});
	}
	dfs_far(0, -1);
	dfs_spread(0, -1);
	vector<query> quer(q);
	for (int i = 0; i < q; i++) {
		query x;
		cin >> x.u >> x.v >> x.a >> x.b;
		x.u--;
		x.v--;
		x.idx = i;
		quer[i] = x;
	}
	queue<pair<int, vector<query>>> que;
	que.emplace(0, quer);
	vector<lint> ret(q);
	while (sz(que)) {
		auto [x, quer] = que.front();
		que.pop();
		x = get_center(x);
		vis[x] = 1;
		lab[x] = -1;
		int C = x;
		int cnt = 0;
		vector<int> vtx;
		vector<vector<query>> qry;
		dep[x] = 0;
		for (auto &[w, y] : gph[x]) {
			if (!vis[y]) {
				DK[y] = 0;
				dep[y] = w;
				par[y] = x;
				dfs2(y, x, cnt++);
				vtx.push_back(y);
			}
		}
		par[C] = C;
		upload[C].clear();
		for (auto &x : ord) {
			if (par[x] != C) {
				F2[x] = max(F2[x], F2[par[x]]);
			}
			upload[x].clear();
		}
		ord.clear();
		qry.resize(cnt);
		auto just = [&](int v, lint A) {
			lint ans = T1[v] * A;
			if (lab[v] != -1 && lab[par[v]] != -1) {
				ans = max(ans, dep[v] * A + A * F2[v]);
			}
			return ans;
		};
		auto root = [&](int v, lint A, lint B, int av) { // A comes from ryute
			vector<int> to_avoid = {vtx[lab[v]]};
			if (av != -1)
				to_avoid.push_back(vtx[av]);
			lint ans = A * far_avoid(C, to_avoid) + just(v, B);
			ans = max(ans, B * T1[v] + A * DK[v]);
			return ans;
		};
		for (auto &q : quer) {
			if (lab[q.u] != lab[q.v]) {
				if (lab[q.u] > lab[q.v])
					swap(q.u, q.v), swap(q.a, q.b);
				if (lab[q.u] == -1) {
					ret[q.idx] = max(ret[q.idx], root(q.v, q.a, q.b, -1));
					upload[q.v].push_back({q.a, q.b, q.idx, 1ll * q.b * dep[q.v]});
				} else {
					ret[q.idx] = max(ret[q.idx], root(q.v, q.a, q.b, lab[q.u]) + 1ll * dep[q.u] * q.a);
					ret[q.idx] = max(ret[q.idx], root(q.u, q.b, q.a, lab[q.v]) + 1ll * dep[q.v] * q.b);
					upload[q.v].push_back({q.a, q.b, q.idx, 1ll * dep[q.u] * q.a + 1ll * dep[q.v] * q.b});
					upload[q.u].push_back({q.b, q.a, q.idx, 1ll * dep[q.v] * q.b + 1ll * dep[q.u] * q.a});
					ret[q.idx] = max(ret[q.idx], just(q.u, q.a) + just(q.v, q.b));
				}
			} else {
				qry[lab[q.u]].push_back(q);
			}
		}
		dfs_query(C, -1, ret);
		for (int i = 0; i < cnt; i++) {
			if (sz(qry[i]))
				que.emplace(vtx[i], qry[i]);
		}
	}
	for (auto &x : ret)
		cout << x << "\n";
}