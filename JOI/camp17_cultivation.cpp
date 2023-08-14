#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 1050;

vector<lint> cy;

struct node {
	int cmin, cmax, gap;
	node() {
		cmin = 2e9;
		cmax = -2e9;
		gap = 0;
	}
	node(int pos) {
		cmin = cmax = pos;
		gap = 0;
	}
	node(int fuck1, int fuck2, int fuck3) {
		cmin = fuck1;
		cmax = fuck2;
		gap = fuck3;
	}
	node operator+(const node &nd) {
		if (cmax < 0)
			return nd;
		if (nd.cmax < 0)
			return *this;
		return node(cmin, nd.cmax, max({gap, nd.gap, nd.cmin - cmax - 1}));
	}
};

struct seg {
	node tree[MAXT];
	int lim;
	void init(int sz) {
		for (lim = 1; lim <= sz; lim <<= 1)
			;
		fill(tree, tree + MAXT, node());
	}
	void upd(int x, int cnt) {
		if (cnt == 0)
			tree[x + lim] = node();
		else
			tree[x + lim] = node(cy[x]);
		x += lim;
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}
} seg;

int cnt[696];
pi dq[3][696];
int fr[3], ed[3];

struct foo {
	int a, b, c;
} f[305][305];

lint sumFixed(lint r, lint c, lint g, vector<pi> &a) {
	vector<array<lint, 3>> e1, e2, event;
	e1.push_back({0, -1, 0});
	for (auto &[x, y] : a) {
		e1.push_back({x, y, +1});
		e2.push_back({x + 1 + g, y, -1});
	}
	e2.push_back({r + g, -1, 0});
	event.resize(sz(e1) + sz(e2));
	merge(all(e1), all(e2), event.begin());
	vector<array<lint, 5>> chop;
	int in = 0, out = 0;
	for (int i = 0; i < sz(event);) {
		int j = i;
		while (j < sz(event) && event[i][0] == event[j][0]) {
			if (event[j][2] > 0)
				in++;
			else if (event[j][2] < 0)
				out++;

			j++;
		}
		if (j == sz(event))
			break;
		if (in > out)
			chop.push_back({event[i][0], event[j][0], f[out][in - 1].a, f[out][in - 1].b, f[out][in - 1].c});
		else {
			chop.push_back({event[i][0], event[j][0], lint(1e18), lint(1e18), lint(1e18)});
		}
		i = j;
	}
	int k = 0;
	memset(fr, 0, sizeof(fr));
	memset(ed, 0, sizeof(ed));
	lint ans = 1e18;
	for (int i = 0; i < sz(chop); i++) {
		if (chop[i][0] > g)
			break;
		while (k < sz(chop) && chop[k][0] < chop[i][0] + r) {
			for (int t = 0; t < 3; t++) {
				pi val = {chop[k][t + 2], chop[k][1]};
				while (fr[t] < ed[t] && dq[t][ed[t] - 1][0] <= val[0])
					ed[t]--;
				dq[t][ed[t]++] = val;
			}
			k++;
		}
		lint dap[3] = {0, 0, 0};
		for (int t = 0; t < 3; t++) {
			while (fr[t] < ed[t] && dq[t][fr[t]][1] <= chop[i][0])
				fr[t]++;
			dap[t] = dq[t][fr[t]][0];
		}
		ans = min(ans, max(dap[0] + dap[1], dap[2]));
	}
	return ans;
}

map<pi, lint> mp;
// abandon
lint solve(lint r, lint c, lint dl, lint dr, vector<pi> &a, lint jasal) {
	if (mp.count({dl, dr}))
		return mp[pi{dl, dr}];
	vector<array<lint, 3>> e1, e2, event;
	for (auto &[x, y] : a) {
		int l = max(0ll, x - dl);
		int e = min(r * 1ll, x + 1 + dr);
		e1.push_back({l, y, +1});
		e2.push_back({e, y, -1});
	}
	event.resize(sz(e1) + sz(e2));
	merge(all(e1), all(e2), event.begin());
	if (event[0][0] != 0 || event.back()[0] != r)
		return mp[pi{dl, dr}] = 1e18;

	int lmax = 0, rmax = 0, lrmax = 0;
	int in = 0, out = 0;
	for (int i = 0; i < sz(event);) {
		int j = i;
		while (j < sz(event) && event[i][0] == event[j][0]) {
			if (event[j][2] > 0)
				in++;
			else if (event[j][2] < 0)
				out++;

			j++;
		}
		if (j == sz(event))
			break;
		if (in == out)
			return 1e18;

		lmax = max(lmax, f[out][in - 1].a);
		rmax = max(rmax, f[out][in - 1].b);
		lrmax = max(lrmax, f[out][in - 1].c);
		if (lmax + rmax >= jasal || lrmax >= jasal)
			return 1e18;
		i = j;
	}
	return mp[pi{dl, dr}] = max(lmax + rmax, lrmax);
}

// n^3 log n

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, r, c;
	cin >> r >> c >> n;
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y, x--, y--;
	sort(all(a));
	lint ans = 2ll * (r + c);
	vector<lint> gaps = {0};
	for (int i = 0; i < n; i++) {
		cy.push_back(a[i][1]);
		for (int j = i + 1; j < n; j++) {
			if (a[j][0] > a[i][0])
				gaps.push_back(a[j][0] - a[i][0] - 1);
		}
	}
	sort(all(cy));
	cy.resize(unique(all(cy)) - cy.begin());
	for (int i = 0; i < n; i++) {
		a[i][1] = lower_bound(all(cy), a[i][1]) - cy.begin();
	}
	sort(all(gaps));
	gaps.resize(unique(all(gaps)) - gaps.begin());

	for (int i = 0; i < n; i++) {
		seg.init(sz(cy));
		memset(cnt, 0, sizeof(cnt));
		for (int j = i; j < n; j++) {
			cnt[a[j][1]] += 1;
			if (cnt[a[j][1]] == 1) {
				seg.upd(a[j][1], cnt[a[j][1]]);
			}
			f[i][j].a = seg.tree[1].cmin;
			f[i][j].b = c - 1 - seg.tree[1].cmax;
			f[i][j].c = seg.tree[1].gap;
		}
	}

	for (auto &dy : gaps) {
		if (ans > dy) {
			ans = min(ans, sumFixed(r, c, dy, a) + dy);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= 0; j--) {
			if (a[i][0] + r - 1 - a[j][0] >= ans)
				break;
			lint jsp = ans - (a[i][0] + r - 1 - a[j][0]);
			ans = min(ans, a[i][0] + r - 1 - a[j][0] + solve(r, c, a[i][0], r - 1 - a[j][0], a, jsp));
		}
	}
	cout << ans << endl;
}