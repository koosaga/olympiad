#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<lint>> conc;
	vector<lint> conv;
	for (int i = 0; i < n; i++) {
		vector<lint> p(m);
		for (auto &x : p)
			cin >> x;
		if (is_sorted(all(p))) {
			vector<lint> q(m + 1);
			for (int j = 0; j < m; j++)
				q[j + 1] = q[j] + p[j];
			conc.push_back(q);
		} else {
			for (auto &y : p)
				conv.push_back(y);
		}
	}
	sort(all(conc), [&](vector<lint> &a, vector<lint> &b) { return a.back() > b.back(); });
	vector<lint> dap(sz(conc) * m + 1);
	vector<lint> sums(sz(conc) + 1);
	for (int i = 0; i < sz(conc); i++)
		sums[i + 1] = sums[i] + conc[i].back();
	{
		vector<lint> records(m + 1);
		for (int i = sz(conc) - 1; i >= 0; i--) {
			for (int j = 0; j <= m; j++) {
				records[j] = max(records[j], conc[i][j]);
			}
			for (int j = 0; j <= m; j++) {
				dap[i * m + j] = max(dap[i * m + j], sums[i] + records[j]);
			}
		}
	}
	{
		vector<lint> records(m + 1, 1e18);
		for (int i = 0; i < sz(conc); i++) {
			for (int j = 0; j <= m; j++)
				records[j] = min(records[j], conc[i].back() - conc[i][j]);
			for (int j = 0; j <= m; j++) {
				dap[i * m + j] = max(dap[i * m + j], sums[i + 1] - records[j]);
			}
		}
	}
	sort(all(conv));
	reverse(all(conv));
	lint sum = 0, ans = 0;
	for (int i = 0; i <= k; i++) {
		ans = max(ans, sum + dap[min(k - i, sz(dap) - 1)]);
		if (i < sz(conv))
			sum += conv[i];
	}
	cout << ans << "\n";
}