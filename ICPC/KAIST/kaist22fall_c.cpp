#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

const int MAXA = 26;
struct SuffixAutomaton {
	struct node {
		int nxt[MAXA], len, slink;
		node() {
			memset(nxt, -1, sizeof(nxt));
			len = slink = 0;
		}
		node(int _len, int _slink) {
			memset(nxt, -1, sizeof(nxt));
			len = _len;
			slink = _slink;
		}
	};
	vector<node> sa;
	int total;
	SuffixAutomaton() {
		total = 0;
		// sa.reserve(2000005);
		sa.push_back(node(0, -1));
	}
	void addChar(int c) {
		assert(0 <= c && c < MAXA);
		sa.push_back(node(sa[total].len + 1, 0));
		int p = total;
		total = sz(sa) - 1;
		while (p != -1 && sa[p].nxt[c] == -1) {
			sa[p].nxt[c] = total;
			p = sa[p].slink;
		}
		if (p != -1) {
			int prv = sa[p].nxt[c];
			int upd = sa[p].nxt[c];
			if (sa[p].len + 1 < sa[prv].len) {
				upd = sz(sa);
				node nd = sa[prv];
				nd.len = sa[p].len + 1;
				sa.push_back(nd);
				sa[prv].slink = upd;
				for (int j = p; j != -1 && sa[j].nxt[c] == prv; j = sa[j].slink) {
					sa[j].nxt[c] = upd;
				}
			}
			sa[total].slink = upd;
		}
	}
};

const int MAXN = 300005;
vector<pi> gph[MAXN];
vector<int> tr[MAXN];
lint dp[MAXN];
lint sum[MAXN][27], comp[MAXN][27];
int M;

lint dfs(int x) {
	if (~dp[x])
		return dp[x];
	lint ret = 0;
	if (x >= M)
		ret++;
	for (auto &[_, y] : gph[x]) {
		ret += dfs(y);
	}
	return dp[x] = ret;
}

int par[19][MAXN];

void dfs2(int x, SuffixAutomaton &sa) {
	for (int i = 0; i < 26; i++) {
		if (sa.sa[x].nxt[i] != -1) {
			comp[x][i] += dp[M - 1 + sa.sa[x].nxt[i]];
		}
	}
	if (x > 0)
		comp[x][26]++;
	for (int i = 0; i < 27; i++) {
		sum[x][i] += comp[x][i] * (x ? (sa.sa[x].len - sa.sa[par[0][x]].len) : 1);
	}
	for (auto &y : tr[x]) {
		for (int j = 0; j < 27; j++) {
			sum[y][j] = sum[x][j];
		}
		dfs2(y, sa);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	string s, t;
	lint k;
	cin >> s >> t >> k;
	/*s.clear();
	t.clear();
	for (int i = 0; i < 75000; i++) {
		s.push_back('a');
		t.push_back('a');
	}*/
	SuffixAutomaton t1, t2;
	for (auto &z : s) {
		t1.addChar(z - 'a');
	}
	for (auto &z : t) {
		t2.addChar(z - 'a');
	}
	for (int i = 0; i < sz(t1.sa); i++) {
		for (int j = 0; j < MAXA; j++) {
			if (t1.sa[i].nxt[j] != -1) {
				gph[i].push_back({j, t1.sa[i].nxt[j]});
			}
		}
		if (i > 0) {
			for (int j = 0; j < MAXA; j++) {
				if (t2.sa[0].nxt[j] != -1) {
					gph[i].push_back({j, sz(t1.sa) + t2.sa[0].nxt[j]});
				}
			}
		}
		sort(all(gph[i]));
	}
	for (int i = 0; i < sz(t2.sa); i++) {
		for (int j = 0; j < MAXA; j++) {
			if (t2.sa[i].nxt[j] != -1) {
				gph[i + sz(t1.sa)].push_back({j, t2.sa[i].nxt[j] + sz(t1.sa)});
			}
		}
	}
	memset(dp, -1, sizeof(dp));
	M = sz(t1.sa) + 1;
	dfs(0);
	if (k > dp[0]) {
		cout << "-1\n";
		return 0;
	}
	vector<int> dep(sz(t2.sa));
	for (int i = 1; i < sz(t2.sa); i++) {
		tr[t2.sa[i].slink].push_back(i);
		dep[i] = t2.sa[i].len;
		par[0][i] = t2.sa[i].slink;
	}
	for (int i = 1; i < 19; i++) {
		for (int j = 0; j < sz(t2.sa); j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	dfs2(0, t2);
	auto solve = [&](lint k) {
		string path;
		int apath = 0, L = 0, R = 0, bpathMax = 0;
		auto getSum = [&](int v, int r, int k) {
			if (r < 0)
				return 0ll;
			if (v == 0 || r == 0)
				return sum[0][k];
			for (int i = 18; i >= 0; i--) {
				if (dep[par[i][v]] > r)
					v = par[i][v];
			}
			return (comp[v][k]) * (r - dep[par[0][v]]) + sum[par[0][v]][k];
		};
		while (k > 0) {
			if (sz(path)) {
				k -= getSum(bpathMax, R, 26) - getSum(bpathMax, L - 1, 26);
			}
			if (k <= 0)
				break;
			for (int i = 0; i < 26; i++) {
				lint tmp = 0;
				if (~apath && t1.sa[apath].nxt[i] != -1) {
					tmp += dp[t1.sa[apath].nxt[i]];
				}
				if (sz(path) > 0) {
					tmp += getSum(bpathMax, R, i) - getSum(bpathMax, L - 1, i);
				}
				if (k <= tmp) {
					path.push_back(i + 'a');
					if (~apath)
						apath = t1.sa[apath].nxt[i];
					if (sz(path) > 1) {
						// organize path
						while (bpathMax && t2.sa[bpathMax].nxt[i] == -1) {
							bpathMax = t2.sa[bpathMax].slink;
							R = t2.sa[bpathMax].len;
						}
						if (t2.sa[bpathMax].nxt[i] != -1) {
							bpathMax = t2.sa[bpathMax].nxt[i];
							R++;
						}
						if (~apath)
							L = 0;
						else
							L++;
					}
					break;
				}
				k -= tmp;
			}
		}
		return path;
	};
	cout << solve(k) << "\n";
}