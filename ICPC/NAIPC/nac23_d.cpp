#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

struct node {
	long double c;
	long double p;
	int idx;
	bool operator<(const node &nd) const { return c * (1 - nd.p) > nd.c * (1 - p); } // reverse!!
};

priority_queue<node> pq;

pi ch[MAXN];
vector<int> ans;
bool fucked[MAXN];

void dfs(int v, int n) {
	if (v < n) {
		if (v)
			ans.push_back(v);
		return;
	}
	dfs(ch[v][0], n);
	dfs(ch[v][1], n);
}

struct disj2 {
	int pa[MAXN];
	void init() { iota(pa, pa + MAXN, 0); }
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q, int n) {
		p = find(p);
		q = find(q);
		ch[n] = {p, q};
		pa[q] = n;
		pa[p] = n;
		return 1;
	}
} disj2;
struct disj {
	int pa[MAXN];
	node nd[MAXN];
	int count;
	void init(int n, vector<int> c, vector<double> p) {
		count = n;
		for (int i = 0; i < n; i++) {
			pa[i] = i;
			nd[i] = {c[i], p[i], i};
		}
		for (int i = 1; i < n; i++) {
			pq.push(nd[i]);
		}
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool validate(node x) {
		if (fucked[x.idx])
			return false;
		if (find(x.idx) != x.idx)
			return false;
		if (nd[x.idx].c != x.c)
			return false;
		if (fabs(nd[x.idx].p - x.p) > 1e-9)
			return false;
		return true;
	}
	bool uni(int par, int me) {
		par = find(par);
		me = find(me);
		assert(par != me);
		pa[me] = par;
		disj2.uni(par, me, count++);
		nd[par].c += nd[me].c * nd[par].p;
		nd[par].p *= nd[me].p;
		fucked[me] = 1;
		if (par)
			pq.push(nd[par]);
		return 1;
	}
} disj;

vector<int> solve(int n, vector<int> c, vector<double> p, vector<int> par) {
	disj.init(n, c, p);
	disj2.init();
	while (sz(pq)) {
		auto x = pq.top();
		pq.pop();
		if (!disj.validate(x))
			continue;
		//	cout << x.c / (1 - x.p) << endl;
		//	cout << "merge " << x.idx << endl;
		disj.uni(par[x.idx], x.idx);
	}
	ans.clear();
	dfs(disj.count - 1, n);
	return ans;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	n++;
	vector<int> c(n);
	vector<double> p(n);
	p[0] = 1;
	vector<int> par(n);
	for (int i = 1; i < n; i++) {
		cin >> c[i] >> p[i] >> par[i];
	}
	auto x = solve(n, c, p, par);
	double prob = 1, ans = 0;
	for (int i = 0; i < sz(x); i++) {
		cout << x[i] << "\n";
		ans += c[x[i]] * prob;
		prob *= p[x[i]];
	}
	return 0;

	cerr << ans << "\n";
	vector<int> ord(n - 1);
	iota(all(ord), 1);
	double rans = 1e18;
	do {
		double prob = 1, ans = 0;
		vector<int> mark(n);
		mark[0] = 1;
		for (int i = 0; i < n - 1; i++) {
			if (!mark[par[ord[i]]])
				ans = 1e18;
			mark[ord[i]] = 1;
			ans += c[ord[i]] * prob;
			prob *= p[ord[i]];
		}
		rans = min(rans, ans);
	} while (next_permutation(all(ord)));
	cout << rans << endl;
}