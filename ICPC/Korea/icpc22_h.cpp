#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct SuffixAutomaton {
	struct node {
		int nxt[26], len, slink;
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
		assert(0 <= c && c < 26);
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

const int MAXN = 100005;
vector<int> gph[MAXN];
int val[MAXN], dep[MAXN], idx[MAXN];
pi ans[MAXN];
set<int> s[MAXN];

int query(int p, int l) {
	auto it = s[p].begin();
	int ans = 0;
	while (it != s[p].end()) {
		ans++;
		it = s[p].lower_bound(*it + l);
	}
	return ans;
}

void dfs(int x) {
	if (~val[x])
		s[idx[x]].insert(val[x]);

	for (auto &y : gph[x]) {
		dfs(y);
		int l = dep[x] + 1, r = dep[y], occ = sz(s[idx[y]]);
		int Q = query(idx[y], l);
		while (l != r) {
			int m = (l + r + 1) / 2;
			if (query(idx[y], m) == Q)
				l = m;
			else
				r = m - 1;
		}
		ans[occ] = max(ans[occ], pi{Q, l});
		if (sz(s[idx[x]]) < sz(s[idx[y]]))
			swap(idx[x], idx[y]);
		for (auto &z : s[idx[y]])
			s[idx[x]].insert(z);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	string s;
	cin >> s;
	SuffixAutomaton sa;
	vector<int> suf;
	for (auto &x : s) {
		sa.addChar(x - 'a');
		suf.push_back(sa.total);
	}
	for (int i = 1; i < sz(sa.sa); i++) {
		dep[i] = sa.sa[i].len;
		gph[sa.sa[i].slink].push_back(i);
	}
	iota(idx, idx + sz(sa.sa), 0);
	memset(val, -1, sizeof(val));
	for (int i = 0; i < sz(suf); i++) {
		val[suf[i]] = i;
	}
	dfs(0);
	for (int i = 1; i <= sz(s); i++)
		cout << ans[i][1] << " ";
}