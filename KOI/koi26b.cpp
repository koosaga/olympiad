#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;
int nl[20][MAXN], nr[20][MAXN];

struct bit {
	int tree[MAXN];
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	set<int> s;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		s.insert(i);
	}
	vector<int> v;
	for (int i = 1; i < n - 1; i++) {
		if (a[i - 1] > a[i] && a[i] < a[i + 1]) {
			v.push_back(i);
		}
	}
	vector<int> T(n, 1e9);
	for (int t = 1; sz(v); t++) {
		for (auto &x : v) {
			s.erase(x);
			T[x] = t;
		}
		vector<int> nxt;
		for (auto &x : v) {
			auto it = s.lower_bound(x);
			if (it != s.begin())
				nxt.push_back(*prev(it));
			if (it != s.end())
				nxt.push_back(*it);
		}
		v.clear();
		sort(all(nxt));
		nxt.resize(unique(all(nxt)) - nxt.begin());
		for (auto &x : nxt) {
			auto i1 = s.lower_bound(x);
			auto i2 = s.upper_bound(x);
			if (i1 != s.begin() && i2 != s.end() && a[*prev(i1)] > a[x] && a[x] < a[*i2])
				v.push_back(x);
		}
	}
	vector<int> stk = {-1};
	for (int i = 0; i < n; i++) {
		while (sz(stk) > 1 && a[stk.back()] < a[i])
			stk.pop_back();
		nl[0][i] = stk.back();
		stk.push_back(i);
	}
	stk.clear();
	stk.push_back(n);
	nr[0][n] = n;
	for (int i = n - 1; i >= 0; i--) {
		while (sz(stk) > 1 && a[stk.back()] < a[i])
			stk.pop_back();
		nr[0][i] = stk.back();
		stk.push_back(i);
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j <= n; j++) {
			nr[i][j] = nr[i - 1][nr[i - 1][j]];
			nl[i][j] = (nl[i - 1][j] >= 0 ? nl[i - 1][nl[i - 1][j]] : -1);
		}
	}
	vector<int> ans(q);
	vector<array<int, 4>> events;
	for (int i = 0; i < q; i++) {
		int l, r, t;
		cin >> l >> r >> t;
		events.push_back({t, l - 1, r - 1, i});
		int p = l - 1;
		int ii = i;
		for (int i = 19; i >= 0; i--) {
			if (nr[i][p] < r && T[nr[i][p]] <= t) {
				ans[ii] += (1 << i);
				p = nr[i][p];
			}
		}
		if (T[p] <= t)
			ans[i]++;
		p = r - 1;
		for (int i = 19; i >= 0; i--) {
			if (nl[i][p] >= l - 1 && T[nl[i][p]] <= t) {
				ans[ii] += (1 << i);
				p = nl[i][p];
			}
		}
		if (nl[0][p] >= l - 1 && T[p] <= t)
			ans[i]++;
	}
	sort(all(events));
	reverse(all(events));
	vector<pi> points;
	for (int i = 0; i < n; i++) {
		points.push_back({T[i], i});
	}
	sort(all(points));
	int j = 0;
	reverse(all(points));
	for (int i = 0; i < sz(events); i++) {
		while (j < sz(points) && points[j][0] > events[i][0]) {
			bit.add(points[j++][1] + 1, +1);
		}
		ans[events[i][3]] += bit.query(events[i][2] + 1) - bit.query(events[i][1]);
	}
	for (int i = 0; i < q; i++) {
		cout << ans[i] << "\n";
	}
}