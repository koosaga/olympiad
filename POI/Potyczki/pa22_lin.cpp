#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 1; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 1; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

struct disj {
	int pa[MAXN], rk[MAXN];
	lint addi[MAXN];
	void init(int n) {
		fill(rk, rk + n, 0);
		fill(addi, addi + n, 0);
		iota(pa, pa + n, 0);
	}
	int find(int x) { return pa[x] == x ? x : find(pa[x]); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		if (rk[p] > rk[q])
			swap(p, q);
		pa[p] = q;
		addi[p] -= addi[q];
		if (rk[p] == rk[q])
			rk[q]++;
		return 1;
	}
	void increment(int p, lint v) { addi[find(p)] += v; }
	lint query(int p) {
		lint ans = 0;
		while (pa[p] != p) {
			ans += addi[p];
			p = pa[p];
		}
		ans += addi[p];
		return ans;
	}
} disj;

vector<lint> solve_one(vector<int> a) {
	int n = sz(a);
	vector<lint> ans(n);
	for (int i = 0; i < n; i++)
		ans[i] = i;
	vector<int> f(n), g(n);
	for (int i = 0; i < n; i++) {
		f[i] = a[i];
		g[a[i]] = i;
	}
	for (int i = n - 2; i >= 0; i--) {
		f[i] = min(f[i], f[i + 1]);
		g[i] = min(g[i], g[i + 1]);
	}
	vector<vector<pi>> event(n);
	for (int i = 0; i < n; i++) {
		bit.add(a[i], +1);
		event[i].push_back({a[i], i});
	}
	disj.init(n);
	for (int i = n - 1; i >= 0; i--) {
		bit.add(a[i], -1);
		priority_queue<pi> pq;
		for (auto &v : event[i]) {
			pq.push(v);
		}
		while (sz(pq)) {
			auto [j, idx] = pq.top();
			pq.top();
			vector<int> indices;
			while (sz(pq) && pq.top()[0] == j) {
				disj.uni(pq.top()[1], idx);
				pq.pop();
			}
			int Q = bit.query(j - 1);
			if (Q == 0)
				continue;
			disj.increment(idx, Q);

			if (g[j] < i) {
				event[g[j]].push_back({f[i], idx});
			} else {
				pq.push({f[i], idx});
			}
		}
	}
	for (int i = 0; i < n; i++) {
		ans[i] += disj.query(i);
	}
	return ans;
}

void solve(vector<int> a) {
	auto s1 = solve_one(a);
	for (int i = 0; i < sz(a); i++) {
		a[i] = sz(a) - 1 - a[i];
	}
	reverse(all(a));
	auto s2 = solve_one(a);
	reverse(all(s2));
	for (int i = 0; i < sz(a); i++)
		cout << s1[i] + s2[i] << " ";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	vector<int> v;
	int mx = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
		mx = max(mx, a[i]);
		if (mx == i)
			v.push_back(i + 1);
	}
	for (int i = 0; i < sz(v); i++) {
		int l = (i ? v[i - 1] : 0);
		int r = v[i];
		vector<int> b(a.begin() + l, a.begin() + r);
		for (auto &z : b)
			z -= l;
		solve(b);
	}
	cout << "\n";
}