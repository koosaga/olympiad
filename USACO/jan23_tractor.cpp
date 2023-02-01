#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using line = array<lint, 3>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;

struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;
vector<int> gph[MAXN];
int lev[MAXN], par[MAXN], dout[MAXN], piv;
void dfs(int x) {
	for (auto &y : gph[x]) {
		dfs(y);
	}
	dout[x] = piv++;
}

int dist(int u, int v) { return lev[v] - lev[u] + (dout[u] < dout[v]); }

struct event {
	int pos, l, r, dx, idx;
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	string s, t;
	cin >> s >> t;
	int Lidx = 0, Ridx = 0;
	vector<pi> intvs(n);
	for (int i = 0; i < 2 * n; i++) {
		if (s[i] == 'L') {
			intvs[Lidx++][0] = i;
		} else {
			intvs[Ridx++][1] = i;
		}
	}
	int j = 0;
	for (int i = 1; i < n; i++) {
		while (j < i && intvs[j][1] < intvs[i][0])
			j++;
		gph[j].push_back(i);
		lev[i] = lev[j] + 1;
	}
	dfs(0);
	vector<pi> v;
	vector<int> rev(n);
	for (int i = 0; i < n; i++) {
		rev[dout[i]] = i;
		//	v.push_back({i, dout[i]});
	}
	vector<pi> quer(q);
	vector<event> vect;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		quer[i][0] = dist(a, b);
		if (dout[a] < dout[b]) {
			vect.push_back({dout[a], a, b, +1, i});
			vect.push_back({dout[b] - 1, a, b, -1, i});
			vect.push_back({n - 1, a, b, +1, i});
		} else {
			vect.push_back({dout[b] - 1, a, b, -1, i});
			vect.push_back({dout[a], a, b, +1, i});
		}
	}
	sort(all(vect), [&](const event &a, const event &b) { return a.pos < b.pos; });
	j = 0;
	for (auto &x : vect) {
		while (j <= x.pos) {
			if (t[rev[j]] == '1')
				bit.add(rev[j], +1);
			j++;
		}
		quer[x.idx][1] += x.dx * (bit.query(x.r) - bit.query(x.l - 1));
	}
	for (auto &[a, b] : quer)
		cout << a << " " << b << "\n";
}
