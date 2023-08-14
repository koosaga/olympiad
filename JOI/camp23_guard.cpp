#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

// case tree:
// root with maximum
// anchor in parent
// using the guard from root, can do everything

struct disj {
	int pa[MAXN], mx[MAXN];
	void init(int n, lint *a) {
		iota(pa, pa + n + 1, 0);
		for (int i = 0; i < n; i++)
			mx[i] = a[i];
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	int query(int x) { return mx[find(x)]; }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		mx[p] = min(mx[p], mx[q]);
		return 1;
	}
} disj;

using node = array<lint, 3>;
priority_queue<pi, vector<pi>, greater<pi>> pq[MAXN];
priority_queue<node, vector<node>, greater<node>> global;

vector<pi> gph[MAXN];
lint a[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<array<int, 3>> edges(m);
	for (auto &[x, s, e] : edges) {
		cin >> s >> e;
		s--;
		e--;
		x = a[s] + a[e];
	}
	sort(all(edges));
	disj.init(n, a);
	for (auto &[x, s, e] : edges) {
		if (disj.uni(s, e)) {
			pq[s].push({x, e});
			pq[e].push({x, s});
		}
	}
	for (int i = 0; i < n; i++) {
		global.push({pq[i].top()[0] - a[i], i, a[i]});
	}
	disj.init(n, a);
	int rt = min_element(a, a + n) - a;
	lint tot = 1ll * a[rt] * (n - 2) + *max_element(a, a + n);
	vector<lint> ans(q + 1, tot);
	for (int i = n - 2; i >= 0; i--) {
		int v = -1;
		while (sz(global)) {
			auto x = global.top();
			global.pop();
			if (disj.query(x[1]) != x[2])
				continue;
			v = disj.find(x[1]);
			while (sz(pq[v]) && disj.find(v) == disj.find(pq[v].top()[1])) {
				pq[v].pop();
			}
			assert(sz(pq[v]));
			if (pq[v].top()[0] - disj.query(v) != x[0]) {
				global.push({pq[v].top()[0] - disj.query(v), v, disj.query(v)});
				continue;
			}
			break;
		}
		assert(v != -1);
		auto tp = pq[v].top();
		assert(disj.find(tp[1]) != disj.find(v));
		pq[v].pop();
		tot += tp[0] - disj.query(v) - a[rt];
		if (i < sz(ans))
			ans[i] = tot;

		int w = tp[1];
		v = disj.find(v);
		w = disj.find(w);
		disj.uni(v, w); // pa[w] = v;
		if (sz(pq[w]) > sz(pq[v])) {
			swap(pq[w], pq[v]);
		}
		while (sz(pq[w])) {
			auto tp = pq[w].top();
			pq[w].pop();
			if (disj.find(tp[1]) == disj.find(v))
				continue;
			pq[v].push(tp);
		}
		if (sz(pq[v]))
			global.push({pq[v].top()[0] - disj.query(v), v, disj.query(v)});
	}
	for (auto &x : ans)
		cout << x << "\n";
}