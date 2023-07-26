#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

int n;
namespace multidrink {
int par[MAXN], pth[MAXN];
vector<int> gph[MAXN];
int X[MAXN], Z[MAXN];
int dep[MAXN], mxd[MAXN], sz[MAXN];

void dfs2(int x, int p) {
	sz[x] = 1;
	for (auto &i : gph[x]) {
		if (pth[i] || i == p)
			continue;
		dep[i] = dep[x] + 1;
		dfs2(i, x);
		sz[x] += sz[i];
		mxd[x] = max(mxd[x], mxd[i]);
	}
	mxd[x] = max(mxd[x], dep[x]);
	vector<int> gs;
	int leaf = 0;
	for (auto &i : gph[x]) {
		if (pth[i] || i == p)
			continue;
		if (mxd[i] >= dep[x] + 2) {
			gs.push_back(i);
		} else
			leaf++;
	}
	if (gs.empty()) {
		X[x] = 1;
		if (leaf >= 2)
			Z[x] = 1;
	}
	if (gs.size() == 1) {
		X[x] = X[gs[0]];
		Z[x] = (leaf > 0 && X[gs[0]]);
	}
	if (gs.size() == 2) {
		Z[x] = (X[gs[0]] && X[gs[1]]);
	}
}

void dfsX_real(int x, int p, int s, int e, int flg, vector<int> &ret) {
	if (flg == 0)
		ret[s++] = x;
	else
		ret[--e] = x;
	vector<int> gs, lf;
	for (auto &i : gph[x]) {
		if (pth[i] || i == p)
			continue;
		if (mxd[i] >= dep[x] + 2) {
			gs.push_back(i);
		} else
			lf.push_back(i);
	}
	if (gs.empty()) {
		for (auto &i : lf)
			ret[s++] = i;
		return;
	}
	if (gs.size() == 1) {
		if (flg == 0) {
			for (auto &i : lf)
				ret[--e] = i;
			dfsX_real(gs[0], x, s, e, 1, ret);
		} else {
			for (auto &i : lf)
				ret[s++] = i;
			dfsX_real(gs[0], x, s, e, 0, ret);
		}
	}
	if (gs.size() >= 2)
		assert(0);
}

void dfsX(int x, int p, vector<int> &ret) { // from root to bottom
	int s = ret.size(), e = ret.size() + sz[x];
	ret.resize(e);
	dfsX_real(x, p, s, e, 0, ret);
}

void dfsZ(int x, int p, vector<int> &ret) { // Z
	vector<int> gs, lf;
	for (auto &i : gph[x]) {
		if (pth[i] || i == p)
			continue;
		if (mxd[i] >= dep[x] + 2) {
			gs.push_back(i);
		} else
			lf.push_back(i);
	}
	if (gs.empty()) {
		ret.push_back(lf[0]);
		ret.push_back(x);
		for (int i = 1; i < lf.size(); i++)
			ret.push_back(lf[i]);
	}
	if (gs.size() == 1) {
		dfsX(gs[0], x, ret);
		ret.push_back(x);
		for (auto &i : lf)
			ret.push_back(i);
	}
	if (gs.size() == 2) {
		vector<int> lv, rv;
		dfsX(gs[0], x, lv);
		dfsX(gs[1], x, rv);
		for (auto &i : lv)
			ret.push_back(i);
		ret.push_back(x);
		reverse(rv.begin(), rv.end());
		for (auto &i : rv)
			ret.push_back(i);
		for (auto &i : lf)
			ret.push_back(i);
	}
}

void dfs(int x, int p) {
	for (auto &i : gph[x]) {
		if (i != p) {
			par[i] = x;
			dfs(i, x);
		}
	}
}

int in0[MAXN], in1[MAXN], out0[MAXN], out1[MAXN], ok[MAXN];
void addEdge(int u, int v) {
	gph[u + 1].push_back(v + 1);
	gph[v + 1].push_back(u + 1);
}

bool solve(int src, int snk) {
	memset(in0, 0, sizeof(int) * (n + 2));
	memset(out0, 0, sizeof(int) * (n + 2));
	memset(in1, 0, sizeof(int) * (n + 2));
	memset(out1, 0, sizeof(int) * (n + 2));
	memset(pth, 0, sizeof(int) * (n + 2));
	memset(par, 0, sizeof(int) * (n + 2));
	memset(ok, 0, sizeof(int) * (n + 2));
	memset(X, 0, sizeof(int) * (n + 2));
	memset(Z, 0, sizeof(int) * (n + 2));
	memset(dep, 0, sizeof(int) * (n + 2));
	memset(mxd, 0, sizeof(int) * (n + 2));
	memset(sz, 0, sizeof(int) * (n + 2));

	src++;
	snk++;
	dfs(src, -1);
	vector<int> v;
	for (int j = snk; j != src; j = par[j])
		v.push_back(j);
	v.push_back(src);
	reverse(v.begin(), v.end());
	for (auto &i : v)
		pth[i] = 1;
	if (gph[1].size() == 1) {
		out0[1] = 1;
	} else {
		dfs2(1, -1);
		if (X[1])
			out1[1] = 1;
	}
	for (int i = 1; i < v.size(); i++) {
		in0[v[i]] = out0[v[i - 1]] || out1[v[i - 1]];
		in1[v[i]] = out0[v[i - 1]];
		if (v[i] == snk) {
			if (gph[snk].size() == 1)
				out0[snk] = in0[snk];
			else {
				dfs2(v[i], -1);
				if (X[snk])
					out0[snk] = in1[snk];
			}
			break;
		}
		if (gph[v[i]].size() == 2) {
			out0[v[i]] = out1[v[i]] = (in0[v[i]] || in1[v[i]]);
		} else {
			dfs2(v[i], -1);
			if (X[v[i]])
				out1[v[i]] |= in0[v[i]];
			if (X[v[i]])
				out0[v[i]] |= in1[v[i]];
			if (Z[v[i]])
				out1[v[i]] |= in1[v[i]];
		}
	}
	if (!out0[snk]) {
		return false;
	} else {
		vector<int> ord;
		int mode = 0;
		for (int i = v.size() - 1; i > 0; i--) {
			int nxt = -1;
			if (v[i] == snk) {
				if (gph[snk].size() == 1)
					ord.push_back(snk), nxt = 0;
				else {
					vector<int> tmp;
					dfsX(snk, -1, tmp);
					for (auto &i : tmp)
						ord.push_back(i);
					nxt = 1;
				}
			} else {
				if (gph[v[i]].size() == 2) {
					ord.push_back(v[i]);
					if (in0[v[i]])
						nxt = 0;
					else
						nxt = 1;
				} else {
					if (mode == 1 && X[v[i]] && in0[v[i]]) {
						nxt = 0;
						vector<int> tmp;
						dfsX(v[i], -1, tmp);
						reverse(tmp.begin(), tmp.end());
						for (auto &i : tmp)
							ord.push_back(i);
					} else if (mode == 0 && X[v[i]] && in1[v[i]]) {
						nxt = 1;
						vector<int> tmp;
						dfsX(v[i], -1, tmp);
						for (auto &i : tmp)
							ord.push_back(i);
					} else if (mode == 1 && Z[v[i]] && in1[v[i]]) {
						nxt = 1;
						vector<int> tmp;
						dfsZ(v[i], -1, tmp);
						for (auto &i : tmp)
							ord.push_back(i);
					} else
						assert(0);
				}
			}
			if (nxt == 1) {
				mode = 0;
			} else {
				if (out0[v[i - 1]])
					mode = 0;
				else
					mode = 1;
			}
		}
		if (gph[1].size() == 1)
			ord.push_back(1);
		else {
			vector<int> tmp;
			dfsX(1, -1, tmp);
			reverse(tmp.begin(), tmp.end());
			for (auto &i : tmp)
				ord.push_back(i);
		}
		reverse(ord.begin(), ord.end());
		for (auto &i : ord)
			cout << i << " ";
		return true;
	}
}

} // namespace multidrink

vector<int> gph[MAXN], ord;
int par[MAXN], a[MAXN];

void dfs(int x) {
	ord.push_back(x);
	for (auto &y : gph[x]) {
		gph[y].erase(find(all(gph[y]), x));
		dfs(y);
	}
}

lint UG[MAXN];			   // unguarded (need free)
lint G[MAXN];			   // guarded (can B or halt)
lint C[MAXN];			   // caterpillar
int chk[MAXN], snk, cases; // snk: deepest guarded

void fC(int v);
void fG(int v);
void fUG(int v);

array<lint, 3> U0[MAXN][2][2] = {};
array<lint, 3> U1[MAXN][2][2] = {};
array<lint, 3> U2[MAXN][3][2] = {};
int prio[MAXN];

pi haha(int x) {
	pi ans{0, x};
	for (auto &y : gph[x]) {
		ans = max(ans, haha(y));
	}
	ans[0] += prio[x] * 15571557 + chk[x] * 2 - 1;
	return ans;
}

void fUG(int v) {
	//	cout << "fUG(" << v << ")" << endl;
	snk = v;
	chk[v] = 1;
	prio[v] = 1;
	pi upd{a[v], v};
	for (int i = 0; i < sz(gph[v]) + 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				U0[i][j][k] = array<lint, 3>{0, 0, 0};
			}
		}
	}
	lint sum = a[v];
	for (int i = 1; i <= sz(gph[v]); i++) {
		int w = gph[v][i - 1];
		sum += a[w];
		for (int x = 1; x >= 0; x--) {
			for (int y = 1; y >= 0; y--) {
				U0[i][x][y] = U0[i - 1][x][y];
				if (x)
					U0[i][x][y] = max(U0[i][x][y], array<lint, 3>{U0[i - 1][x - 1][y][0] + C[w] - a[w], i, 1});
				if (y)
					U0[i][x][y] = max(U0[i][x][y], array<lint, 3>{U0[i - 1][x][y - 1][0] + UG[w] - a[w], i, 2});
			}
		}
		upd = max(upd, pi{G[w] + a[v], w}); // free
	}
	if (upd[0] > sum + U0[sz(gph[v])][1][1][0]) {
		int w = upd[1];
		fG(w);
	} else {
		for (int i = 1; i <= sz(gph[v]); i++) {
			int w = gph[v][i - 1];
			chk[w] = 1;
		}
		int g1 = sz(gph[v]);
		int i1 = 1;
		int i2 = 1;
		vector<pair<string, int>> nxt;
		while (U0[g1][i1][i2][2]) {
			g1 = U0[g1][i1][i2][1];
			int w = gph[v][g1 - 1];
			if (U0[g1][i1][i2][2] == 2) {
				nxt.emplace_back("UG", w);
				i2--;
			} else {
				nxt.emplace_back("C", w);
				i1--;
			}
			g1--;
		}
		for (auto &[s, w] : nxt) {
			if (s == "UG")
				fUG(w);
			else
				fC(w);
		}
	}
}

void fG(int v) {
	//	cout << "fG(" << v << ")" << endl;
	snk = v;
	chk[v] = 1;
	for (int i = 0; i < sz(gph[v]) + 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 2; k++) {
				U2[i][j][k] = array<lint, 3>{0, 0, 0};
				if (j < 2)
					U1[i][j][k] = array<lint, 3>{0, 0, 0};
			}
		}
	}
	for (int i = 1; i <= sz(gph[v]); i++) {
		int w = gph[v][i - 1];
		chk[w] = 1;
		for (int x = 1; x >= 0; x--) {
			for (int y = 1; y >= 0; y--) {
				U1[i][x][y] = U1[i - 1][x][y];
				if (x)
					U1[i][x][y] = max(U1[i][x][y], array<lint, 3>{U1[i - 1][x - 1][y][0] + C[w] - a[w], i, 1});
				if (y)
					U1[i][x][y] = max(U1[i][x][y], array<lint, 3>{U1[i - 1][x][y - 1][0] + G[w] - a[w], i, 2});
			}
		}
		for (int x = 2; x >= 0; x--) {
			for (int y = 1; y >= 0; y--) {
				U2[i][x][y] = U2[i - 1][x][y];
				if (x)
					U2[i][x][y] = max(U2[i][x][y], array<lint, 3>{U2[i - 1][x - 1][y][0] + C[w] - a[w], i, 1});
				if (y)
					U2[i][x][y] = max(U2[i][x][y], array<lint, 3>{U2[i - 1][x][y - 1][0] + UG[w] - a[w], i, 2});
			}
		}
	}
	if (max(U1[sz(gph[v])][1][1][0], U2[sz(gph[v])][2][1][0]) == 0)
		return;
	if (U1[sz(gph[v])][1][1][0] > U2[sz(gph[v])][2][1][0]) {
		int g1 = sz(gph[v]);
		int i1 = 1;
		int i2 = 1;
		vector<pair<string, int>> nxt;

		while (U1[g1][i1][i2][2]) {
			g1 = U1[g1][i1][i2][1];
			int w = gph[v][g1 - 1];
			if (U1[g1][i1][i2][2] == 2) {
				nxt.emplace_back("G", w);
				i2--;
			} else {
				nxt.emplace_back("C", w);
				i1--;
			}
			g1--;
		}
		for (auto &[s, w] : nxt) {
			if (s == "G")
				fG(w);
			else
				fC(w);
		}
	} else {
		int g1 = sz(gph[v]);
		int i1 = 2;
		int i2 = 1;
		vector<pair<string, int>> nxt;
		while (U2[g1][i1][i2][2]) {
			g1 = U2[g1][i1][i2][1];
			int w = gph[v][g1 - 1];
			if (U2[g1][i1][i2][2] == 2) {
				nxt.emplace_back("UG", w);
				i2--;
			} else {
				nxt.emplace_back("C", w);
				i1--;
			}
			g1--;
		}
		for (auto &[s, w] : nxt) {
			if (s == "UG")
				fUG(w);
			else
				fC(w);
		}
	}
}

void fC(int v) {
	//	cout << "fC(" << v << ")" << endl;
	cases = v;
	chk[v] = 1;
	pi upd{0, 0};
	for (auto &w : gph[v]) {
		chk[w] = 1;
		upd = max(upd, pi{C[w] - a[w], w}); // take one cat
	}
	if (upd[0] == 0)
		return;
	int w = upd[1];
	fC(w);
}

void solve() {
	dfs(0);
	reverse(all(ord));
	for (auto &v : ord) {
		UG[v] = a[v];
		lint upd = a[v];
		lint U0[2][2] = {};
		for (auto &w : gph[v]) {
			UG[v] += a[w];
			upd = max(upd, G[w] + a[v]); // free
			for (int x = 1; x >= 0; x--) {
				for (int y = 1; y >= 0; y--) {
					if (x)
						U0[x][y] = max(U0[x][y], U0[x - 1][y] + C[w] - a[w]);
					if (y)
						U0[x][y] = max(U0[x][y], U0[x][y - 1] + UG[w] - a[w]);
				}
			}
		}
		UG[v] += U0[1][1];
		if (UG[v] < upd) {
			UG[v] = upd;
		}
		upd = 0;
		C[v] = a[v];
		for (auto &w : gph[v]) {
			C[v] += a[w];
			upd = max(upd, C[w] - a[w]);
		}
		C[v] += upd;
		G[v] = a[v];
		lint U1[2][2] = {};
		lint U2[3][2] = {};
		for (auto &w : gph[v]) {
			G[v] += a[w];
			for (int x = 1; x >= 0; x--) {
				for (int y = 1; y >= 0; y--) {
					if (x)
						U1[x][y] = max(U1[x][y], U1[x - 1][y] + C[w] - a[w]);
					if (y)
						U1[x][y] = max(U1[x][y], U1[x][y - 1] + G[w] - a[w]);
				}
			}
			for (int x = 2; x >= 0; x--) {
				for (int y = 1; y >= 0; y--) {
					if (x)
						U2[x][y] = max(U2[x][y], U2[x - 1][y] + C[w] - a[w]);
					if (y)
						U2[x][y] = max(U2[x][y], U2[x][y - 1] + UG[w] - a[w]);
				}
			}
		}
		G[v] += max(U1[1][1], U2[2][1]);
	}
	fUG(0);
	cout << UG[0] << "\n" << count(chk, chk + n, 1) << "\n";
	lint ans = 0;
	for (int i = 0; i < n; i++) {
		if (chk[i])
			ans += a[i];
	}
	// cout << endl << ans << endl;
	assert(UG[0] == ans);
	for (int i = 0; i < n; i++) {
		for (auto &j : gph[i]) {
			if (chk[i] && chk[j])
				multidrink::addEdge(i, j);
		}
	}
	int w = haha(0)[1];
	multidrink::solve(0, w);
	return;
	int i = 1;
	while (i < n) {
		if (chk[i] && multidrink::solve(0, i)) {
			return;
		}
		i++;
	}
	return;
}

pi dfsFar(int x, int p) {
	pi ret{0, x};
	for (auto &y : gph[x]) {
		if (y == p)
			continue;
		par[y] = x;
		auto z = dfsFar(y, x);
		ret = max(ret, z);
	}
	ret[0] += a[x];
	return ret;
}

vector<int> ans;

void dfs2(int x, int p, int d) {
	if (!d)
		ans.push_back(x);
	for (auto &i : gph[x]) {
		if (i != p) {
			dfs2(i, x, 1 - d);
		}
	}
	if (d)
		ans.push_back(x);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k;
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	for (int i = 0; i < n; i++)
		cin >> a[i];
	if (k == 1) {
		auto [p, l] = dfsFar(0, -1);
		cout << p << "\n";
		vector<int> v;
		for (int j = l;; j = par[j]) {
			v.push_back(j + 1);
			if (j == 0)
				break;
		}
		reverse(all(v));
		cout << sz(v) << "\n";
		for (auto &pth : v) {
			cout << pth << " ";
		}
		return 0;
	}
	if (k == 3) {
		cout << accumulate(a, a + n, 0ll) << "\n" << n << "\n";
		dfs2(0, -1, 0);
		for (auto &pth : ans) {
			cout << pth + 1 << " ";
		}
		return 0;
	}
	if (k == 2) {
		solve();
	}
}