#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

struct bit {
	lint tree[MAXN];
	void add(int x, int v) {
		for (int i = x; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;
vector<lint> S, T;
vector<vector<int>> gph;
vector<vector<array<lint, 3>>> counts;

lint dfs(int x, int y, int r) {
	lint ans = 0;
	if (r - x + 1 <= y - r) {
		for (int i = x; i <= r; i++) {
			counts[y].push_back({S[i] + T[r], lint(1e18), +1});
			counts[r].push_back({S[i] + T[r], lint(1e18), -1});
		}
	} else {
		for (int j = r + 1; j <= y; j++) {
			counts[r].push_back({-lint(1e18), S[j] - T[r], +1});
			if (x > 0)
				counts[x - 1].push_back({-lint(1e18), S[j] - T[r], -1});
		}
	} /*
	 for (int i = x; i <= r; i++) {
		 for (int j = r + 1; j <= y; j++) {
			 if (S[j] - S[i] >= T[r])
				 ans++;
		 }
	 }*/
	int p = 0;
	if (x != r)
		ans += dfs(x, r, gph[r][p++]);
	if (r + 1 != y)
		ans += dfs(r + 1, y, gph[r][p++]);
	return ans;
}

vector<int> cartesian_tree(vector<lint> a) {
	int n = sz(a);
	vector<int> l(n, -1), r(n, n);
	{
		vector<int> stk;
		for (int i = 0; i < n; i++) {
			while (sz(stk) && a[stk.back()] < a[i]) {
				stk.pop_back();
			}
			if (sz(stk))
				l[i] = stk.back();
			stk.push_back(i);
		}
	}
	{
		vector<int> stk;
		for (int i = n - 1; i >= 0; i--) {
			while (sz(stk) && a[stk.back()] <= a[i]) {
				stk.pop_back();
			}
			if (sz(stk))
				r[i] = stk.back();
			stk.push_back(i);
		}
	}
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		int w = -1;
		if (l[i] != -1 && r[i] != n) {
			w = (a[l[i]] >= a[r[i]] ? r[i] : l[i]);
		} else if (l[i] != -1)
			w = l[i];
		else if (r[i] != n)
			w = r[i];
		ans.push_back(w);
	}
	return ans;
}

lint solve(vector<lint> A, vector<lint> B) {
	lint sum = 0;
	int n = sz(A);
	cr(gph, n);
	cr(counts, n + 1);
	auto ct = cartesian_tree(B);
	int rt = -1;
	for (int i = 0; i < n; i++) {
		if (ct[i] == -1)
			rt = i;
		else
			gph[ct[i]].push_back(i);
	}
	S.push_back(0);
	for (int i = 0; i < n; i++) {
		sum += A[i];
		S.push_back(sum);
	}
	T = B;
	dfs(0, n, rt);
	vector<lint> coords = S;
	sort(all(coords));
	coords.resize(unique(all(coords)) - coords.begin());
	lint ans = 0;
	for (int i = 0; i <= n; i++) {
		int pos = lower_bound(all(coords), S[i]) - coords.begin();
		bit.add(pos + 1, +1);
		for (auto &[l, r, dx] : counts[i]) {
			lint s = lower_bound(all(coords), l) - coords.begin();
			lint e = lower_bound(all(coords), r + 1) - coords.begin();
			ans += dx * (bit.query(e) - bit.query(s));
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, t;
	cin >> n >> t;
	vector<lint> h(n), a(n);
	for (auto &x : h)
		cin >> x;
	for (auto &x : a)
		cin >> x;
	vector<lint> A(n), B(n);
	for (int i = 0; i < n; i++) {
		A[i] = (h[i] > a[i] ? (h[i] - a[i]) : ((h[i] - a[i]) * t));
		B[i] = (t + 1) * max(h[i] - a[i], 0ll);
	}
	cout << solve(A, B) << "\n";
}