#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 530000;
struct seq {
	vector<pi> a;
	int cmx;
	seq() { cmx = -1; }
	seq(int x) {
		cmx = x;
		a.push_back({x, 1});
	}
	void push(int x, int mult) {
		x = max(x, cmx - 40);
		while (sz(a) && a.back()[0] < x) {
			if (sz(a) <= 1)
				break;
			if (a[sz(a) - 2][0] < a.back()[0])
				break;

			int prog = min(x, a[sz(a) - 2][0]) - a.back()[0];
			int b = a.back()[1];
			prog = min(prog, 20);
			b = (b + (1 << prog) - 1) / (1 << prog);
			if (a[sz(a) - 2][0] < x) {
				a.pop_back();
				a.back()[1] += b;
			} else if (a[sz(a) - 2][0] > x) {
				a.pop_back();
				mult += b;
			} else {
				mult += b;
				a.pop_back();
				mult += a.back()[1];
				a.pop_back();
			}
		}
		if (sz(a) && a.back()[0] == x) {
			mult += a.back()[1];
			a.pop_back();
		}
		a.push_back({x, mult});
		if (cmx < x) {
			cmx = x;
			{
				int cnt = 0;
				while (sz(a) && cmx - 40 >= a.back()[0]) {
					cnt += a.back()[1];
					a.pop_back();
				}
				if (cnt)
					a.push_back({cmx - 40, cnt});
			}
			{
				int cnt = 0;
				reverse(all(a));
				while (sz(a) && cmx - 40 >= a.back()[0]) {
					cnt += a.back()[1];
					a.pop_back();
				}
				if (cnt)
					a.push_back({cmx - 40, cnt});
				reverse(all(a));
			}
		}
	}
	seq operator+(const seq &s) const {
		seq ret = *this;
		for (auto [x, mult] : s.a) {
			ret.push(x, mult);
		}
		return ret;
	}
	int query() {
		auto pa = a;
		int mxpos = max_element(all(a)) - a.begin();
		for (int i = sz(a) - 1; i > mxpos; i--) {
			int prog = min(20, a[i - 1][0] - a[i][0]);
			a[i - 1][1] += (a[i][1] + (1 << prog) - 1) / (1 << prog);
		}
		for (int i = 0; i < mxpos; i++) {
			int prog = min(20, a[i + 1][0] - a[i][0]);
			a[i + 1][1] += (a[i][1] + (1 << prog) - 1) / (1 << prog);
		}
		int ans = a[mxpos][0];
		while (a[mxpos][1] > 1) {
			ans++;
			a[mxpos][1] = (a[mxpos][1] + 1) / 2;
		}
		a = pa;
		return ans;
	}
};

vector<int> ans;
vector<int> a;
seq DL[300005], DR[300005];

void solve(int s, int e, vector<array<int, 3>> queries) {
	if (e - s == 1) {
		for (auto &[l, r, x] : queries)
			ans[x] = a[s];
		return;
	}
	int m = (s + e) / 2;
	DL[m] = seq();
	for (int i = m - 1; i >= s; i--) {
		DL[i] = DL[i + 1];
		DL[i].push(a[i], 1);
	}
	DR[m - 1] = seq();
	for (int i = m; i < e; i++) {
		DR[i] = DR[i - 1];
		DR[i].push(a[i], 1);
	}
	for (int i = m - 1; i >= s; i--)
		reverse(all(DL[i].a));
	vector<array<int, 3>> L, R;
	for (auto &[l, r, idx] : queries) {
		if (r <= m)
			L.push_back({l, r, idx});
		else if (l >= m)
			R.push_back({l, r, idx});
		else {
			ans[idx] = (DL[l] + DR[r - 1]).query();
		}
	}
	solve(s, m, L);
	solve(m, e, R);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	cr(a, n);
	cr(ans, q);
	for (auto &x : a)
		cin >> x;
	vector<array<int, 3>> query;
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		query.push_back({l, r, i});
	}
	solve(0, n, query);
	for (auto &x : ans)
		cout << x << "\n";
}