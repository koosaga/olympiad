#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using line = array<lint, 3>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

struct node {
	node *ls, *rs;
	lint sum;
	int cnt;
	node() {
		ls = rs = NULL;
		sum = cnt = 0;
	}
} *root[100005];

int n, a[100005], dfn[100005], piv;
vector<int> graph[100005];
int par[100005][17], dep[100005];

void dfs(int x, int p) {
	dfn[++piv] = x;
	par[x][0] = p;
	for (int ii = 0; ii < graph[x].size(); ii++) {
		int i = graph[x][ii];
		if (i != p) {
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

int lca(int a, int b) {
	if (dep[a] > dep[b])
		swap(a, b);
	int dx = dep[b] - dep[a];
	for (int i = 0; i < 17; i++) {
		if ((dx >> i) & 1)
			b = par[b][i];
	}
	for (int i = 16; i >= 0; i--) {
		if (par[a][i] != par[b][i]) {
			a = par[a][i];
			b = par[b][i];
		}
	}
	if (a == b)
		return a;
	return par[a][0];
}

void init(int s, int e, node *p) {
	if (s == e)
		return;
	p->ls = new node();
	p->rs = new node();
	int m = (s + e) / 2;
	init(s, m, p->ls);
	init(m + 1, e, p->rs);
}

vector<pi> v;

void add(int pos, int ps, int pe, int a, int b, node *prev, node *cur) {
	if (ps == pe) {
		cur->cnt = prev->cnt + a;
		cur->sum = prev->sum + b;
		return;
	}
	int pm = (ps + pe) / 2;
	if (pos <= pm) {
		cur->ls = new node();
		cur->rs = prev->rs;
		add(pos, ps, pm, a, b, prev->ls, cur->ls);
	} else {
		cur->ls = prev->ls;
		cur->rs = new node();
		add(pos, pm + 1, pe, a, b, prev->rs, cur->rs);
	}
	cur->cnt = cur->ls->cnt + cur->rs->cnt;
	cur->sum = cur->ls->sum + cur->rs->sum;
}
static char _buffer[1024];
static int _currentChar = 0;
static int _charsNumber = 0;

static inline int _read() {
	if (_charsNumber < 0) {
		exit(1);
	}
	if (!_charsNumber || _currentChar == _charsNumber) {
		_charsNumber = (int)fread(_buffer, sizeof(_buffer[0]), sizeof(_buffer), stdin);
		_currentChar = 0;
	}
	if (_charsNumber <= 0) {
		return -1;
	}
	return _buffer[_currentChar++];
}

static inline lint _readInt() {
	lint c, x, s;
	c = _read();
	while (c <= 32)
		c = _read();
	x = 0;
	s = 1;
	if (c == '-') {
		s = -1;
		c = _read();
	}
	while (c > 32) {
		x *= 10;
		x += c - '0';
		c = _read();
	}
	if (s < 0)
		x = -x;
	return x;
}

int track(int s, int e, node *a, node *b, node *c, node *d, lint silver) {
	if (s == e) {
		lint tmp = a->sum + b->sum - c->sum - d->sum;
		if (silver < tmp)
			return a->cnt + b->cnt - c->cnt - d->cnt;
		else
			return 0;
	}
	int m = (s + e) / 2;
	lint tmp = a->ls->sum + b->ls->sum - c->ls->sum - d->ls->sum;
	if (silver <= tmp) {
		return track(s, m, a->ls, b->ls, c->ls, d->ls, silver) + (a->rs->cnt + b->rs->cnt - c->rs->cnt - d->rs->cnt);
	} else {
		return track(m + 1, e, a->rs, b->rs, c->rs, d->rs, silver - tmp);
	}
}

int main() {
	n = _readInt();
	int m = _readInt();
	int q = _readInt();
	vector<pi> edg;
	vector<vector<pi>> cp(n - 1);
	for (int i = 1; i < n; i++) {
		int s = _readInt();
		int e = _readInt();
		graph[s].push_back(e);
		graph[e].push_back(s);
		edg.push_back({s, e});
	}
	for (int i = 0; i < m; i++) {
		int p, c;
		p = _readInt();
		c = _readInt();
		cp[p - 1].push_back({c, i});
		v.push_back({c, i});
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for (int i = 0; i < n - 1; i++) {
		for (auto &j : cp[i]) {
			j[0] = lower_bound(all(v), j) - v.begin();
		}
	}
	dfs(1, 0);
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j <= n; j++) {
			par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
	root[1] = new node();
	init(0, v.size() - 1, root[1]);
	vector<int> pae(n + 1);
	for (int i = 0; i < n - 1; i++) {
		auto [x, y] = edg[i];
		if (dep[x] > dep[y])
			swap(x, y);
		pae[y] = i;
	}
	for (int i = 2; i <= n; i++) {
		int x = dfn[i];
		auto prev = root[par[x][0]];
		for (auto &j : cp[pae[x]]) {
			auto cur = new node();
			add(j[0], 0, sz(v) - 1, 1, v[j[0]][0], prev, cur);
			prev = cur;
		}
		root[x] = prev;
	}
	while (q--) {
		int a = _readInt();
		int b = _readInt();
		int g = _readInt();
		lint s = _readInt();
		int l = lca(a, b);
		int not_obtained = track(0, sz(v) - 1, root[a], root[b], root[l], root[l], s);
		if (not_obtained > g)
			cout << "-1\n";
		else
			cout << g - not_obtained << "\n";
	}
}