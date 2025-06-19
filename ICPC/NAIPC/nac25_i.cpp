#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;
// Given n positive integers in range [1, m], find a subset that sums to T.
// Runs in time O(nm)
// Source: https://atcoder.jp/contests/abc221/submissions/60912284

vector<int> SubsetSum(const vector<int> &d, int x) {
	auto chmin = [&](int &x, int y) { x = min(x, y); };
	auto chmax = [&](int &x, int y) { x = max(x, y); };

	int n = d.size(), s = 0;
	for (int i = 0; i < n; i++)
		s += d[i];
	if (x < 0 || s < x)
		return {};
	bool flip = (x * 2 < s);
	if (flip)
		x = s - x;
	int si = 0, m = 0;
	while (x > 0 && si < n)
		x -= d[si++];
	for (int i = 0; i < n; i++)
		chmax(m, d[i]);
	int m2 = m * 2 + 1;
	vector<vector<int>> dp(n + 1);
	const int INF = 1001001001;
	for (int i = si; i <= n; i++)
		dp[i] = vector<int>(m2, INF);
	dp[si][m - x] = 0;
	vector<int> res;
	for (int i = si; i <= n; i++) {
		for (int k = m2 - 1; k >= 0; k--) {
			if (k > m) {
				int r = si;
				if (i > si)
					chmin(r, dp[i - 1][k]);
				for (int j = dp[i][k]; j < r; j++) {
					chmin(dp[i][k - d[j]], j + 1);
				}
			}
			if (i < n) {
				chmin(dp[i + 1][k], dp[i][k]);
				if (k < m)
					chmin(dp[i + 1][k + d[i]], dp[i][k]);
			}
		}
		if (dp[i][m] != INF) {
			res = vector<int>(n);
			fill(res.begin(), res.begin() + si, 1);
			int k = m;
			while (1) {
				int j = dp[i][k];
				if (j == 0 && i == si)
					break;
				if (j != INF && j != 0 && k + d[j - 1] < m2 && dp[i][k + d[j - 1]] < j) {
					k += d[j - 1];
					res[j - 1] = 0;
					continue;
				}
				i--;
				if (dp[i][k] != j)
					k -= d[i], res[i] = 1;
			}
			break;
		}
	}
	if (flip)
		for (int i = 0; i < (int)res.size(); i++)
			res[i] ^= 1;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<array<double, 2>> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y;
	vector<int> nlist;
	for (int i = 0; i < n; i++) {
		auto p1 = a[i], p2 = a[(i + 1) % n];
		for (int j = 0; j < 2; j++) {
			if (p1[0] > p2[0])
				swap(p1, p2);
			int s = (int)ceil(p1[0]), e = (int)floor(p2[0]);
			for (int j = s; j <= e; j++) {
				double ratio = (j - p1[0]) / (p2[0] - p1[0]);
				double Y = ratio * (p2[1] - p1[1]) + p1[1];
				nlist.push_back((int)floor(Y));
				if (nlist.back() == 0)
					nlist.pop_back();
			}
			swap(p1[0], p1[1]);
			swap(p2[0], p2[1]);
		}
	}
	int zs = accumulate(all(nlist), 0);
	if (abs(zs) % 2) {
		cout << "-1\n";
		return 0;
	}
	if (sz(nlist) == 0) {
		cout << "0\n";
		return 0;
	}
	sort(all(nlist));
	int tgt = zs / 2, counts = 0;
	for (auto &x : nlist) {
		if (x < 0) {
			counts++;
			tgt -= x;
			x *= -1;
		}
	}
	auto ans = SubsetSum(nlist, tgt);
	if (sz(ans) == 0) {
		cout << "-1\n";
		return 0;
	}
	for (int i = 0; i < counts; i++) {
		ans[i] = 1 - ans[i];
		nlist[i] *= -1;
	}
	vector<int> d;
	for (int i = 0; i < sz(nlist); i++) {
		if (ans[i])
			d.push_back(nlist[i]);
	}
	cout << sz(d) << "\n";
	for (auto &x : d)
		cout << x << "\n";
}