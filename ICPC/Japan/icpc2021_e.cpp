#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 20005;

struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;
lint solve(vector<int> horz, vector<int> A, vector<int> B) {
	int n = sz(horz) + 1, m = sz(A);
	vector<array<int, 3>> edges;
	sort(all(horz));
	set<pi> s;
	for (int i = 0; i < m; i++) {
		s.insert({i, B[i]});
	}
	vector<lint> sums(sz(horz) + 1);
	for (int i = 1; i <= sz(horz); i++)
		sums[i] = sums[i - 1] + horz[i - 1];
	vector<int> idx(m - 1);
	iota(all(idx), 0);
	sort(all(idx), [&](int p, int q) { return A[p] < A[q]; });
	lint ans = 0;
	for (auto &x : idx) {
		auto it = s.upper_bound({x, int(1e9)});
		pi l = *prev(it), r = *it;
		it = s.erase(it);
		s.erase(--it);
		int lpoz = lower_bound(all(horz), A[x] - l[1]) - horz.begin();
		int rpoz = lower_bound(all(horz), A[x] - r[1]) - horz.begin();
		ans += sums[min(lpoz, rpoz)] + 1ll * min(lpoz, rpoz) * max(l[1], r[1]);
		ans += 1ll * A[x] * (n - min(lpoz, rpoz));
		s.insert({l[0], min(l[1], r[1])});
	}
	ans += 1ll * *min_element(all(B)) * (n - 1) + sums.back();
	return ans;
}

int L[MAXN], R[MAXN], pa[MAXN], W[MAXN];

int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }

vector<int> vidx;
vector<int> widx;
int rev[MAXN];

void dfs(int r, int n) {
	if (r < n) {
		rev[r] = sz(vidx);
		vidx.push_back(r);
	} else {
		dfs(L[r], n);
		widx.push_back(W[r]);
		dfs(R[r], n);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<array<int, 3>> edges(m);
	for (auto &[w, u, v] : edges) {
		cin >> u >> v >> w;
	}
	sort(all(edges));
	int ptr = 0;
	iota(pa, pa + MAXN, 0);
	for (auto &[w, u, v] : edges) {
		u = find(u);
		v = find(v);
		if (u == v)
			continue;
		L[ptr + n] = u;
		R[ptr + n] = v;
		W[ptr + n] = w;
		pa[u] = ptr + n, pa[v] = ptr + n;
		ptr++;
	}
	dfs(2 * n - 2, n);
	int k;
	cin >> k;
	vector<int> A(k), B(k);
	for (int i = 0; i < k; i++)
		cin >> A[i] >> B[i];
	{
		int maxpos = max_element(all(A)) - A.begin();
		rotate(A.begin(), A.begin() + maxpos + 1, A.end());
		rotate(B.begin(), B.begin() + maxpos + 1, B.end());
	}
	int p;
	cin >> p;
	vector<int> points(p);
	for (auto &x : points) {
		cin >> x;
		x = rev[x];
	}
	sort(all(points));
	lint sum = accumulate(all(widx), 0ll);
	int ecnt = n - 1;
	vector<int> grids;
	for (int i = 1; i < sz(points); i++) {
		int z = *max_element(widx.begin() + points[i - 1], widx.begin() + points[i]);
		sum -= z;
		ecnt--;
		grids.push_back(z);
	}
	cout << sum * k + ecnt * accumulate(all(B), 0ll) + solve(grids, A, B);
}