#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 305;

int dp[MAXN][MAXN][1 << 7], sum[1 << 7];
vector<int> a, counts;
vector<array<int, 3>> v;

int f(int l, int r, int msk) {
	if (msk == 0)
		return 0;
	if (r - l < sum[msk])
		return 1e9;
	if (~dp[l][r][msk])
		return dp[l][r][msk];
	int ans = min(f(l + 1, r, msk), f(l, r - 1, msk));
	for (int i = 0; i < sz(v); i++) {
		if ((msk >> i) & 1) {
			ans = min(ans, max(v[i][0] - a[l], 0) + max(a[r - 1], v[i][1]) + f(l, r, msk - (1 << i)));
		}
	}
	for (int j = (msk - 1) & msk; j > 0; j = (j - 1) & msk) {
		ans = min(ans, f(l, l + sum[j], j) + f(l + sum[j], r, msk - j));
	}
	return dp[l][r][msk] = ans;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	a.resize(n + 2);
	a[0] = a[n + 1] = 1e6;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	vector<int> idx(k);
	for (auto &x : idx)
		cin >> x;
	idx.push_back(0);
	idx.push_back(n + 1);
	sort(all(idx));
	lint ans = 0;
	for (int i = 1; i < sz(idx); i++) {
		int l = a[idx[i - 1]], r = a[idx[i]];
		if (l > r)
			swap(l, r);
		if (idx[i] - idx[i - 1] > 1)
			v.push_back({l, r, idx[i] - idx[i - 1] - 1});
		else
			ans += max(l, r);
	}
	vector<int> b;
	for (int i = 1; i <= n; i++) {
		if (binary_search(all(idx), i))
			continue;
		else {
			ans += a[i];
			b.push_back(a[i]);
		}
	}
	sort(all(b));
	a = b;
	n = sz(a);
	for (int i = 0; i < sz(v); i++) {
		counts.push_back(v[i][2]);
		sum[1 << i] = v[i][2];
	}
	for (int i = 1; i < (1 << sz(v)); i++) {
		sum[i] = sum[i - (i & -i)] + sum[(i & -i)];
	}
	memset(dp, -1, sizeof(dp));
	ans += f(0, sz(a), (1 << sz(v)) - 1);
	cout << ans - 2 * int(1e6) << "\n";
}