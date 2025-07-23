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
	int n, k;
	cin >> n >> k;
	vector<vector<pi>> gph(n);
	vector<multiset<lint>> dp(n);
	vector<lint> ans(n), hap(n);
	for (int i = 1; i < n; i++) {
		int p, w;
		cin >> p >> w;
		gph[p - 1].push_back({w, i});
	}

	for (int i = n - 1; i >= 0; i--) {
		for (auto &[w, j] : gph[i]) {
			hap[j] += w;
			dp[j].insert(-w);
			if (sz(dp[j]) > k) {
				auto it = --dp[j].end();
				hap[j] -= -*it;
				dp[j].erase(it);
			}
		}
		auto convert = [&](int idx) {
			vector<lint> ans(k + 1);
			int ptr = 0;
			for (auto x : dp[idx]) {
				ans[ptr + 1] = ans[ptr] - x;
				ptr++;
			}
			while (ptr < k) {
				ptr++;
				ans[ptr] = ans[ptr - 1];
			}
			return ans;
		};
		for (auto &[_, j] : gph[i]) {
			if (sz(dp[i]) < sz(dp[j]))
				swap(dp[i], dp[j]);
			if (sz(dp[i]) + sz(dp[j]) <= k) {
				auto it = dp[i].begin();
				vector<lint> topush;
				for (auto &x : dp[j]) {
					topush.push_back(x + *it);
					it = dp[i].erase(it);
				}
				for (auto &x : topush)
					dp[i].insert(x);
				hap[i] += hap[j];
			} else if (sz(dp[j]) * 2 >= k) {
				vector<lint> d1 = convert(i), d2 = convert(j);
				vector<lint> ans(k + 1);
				for (int i = 0; i <= k / 2; i++)
					ans[i] = d1[i] + d2[i];
				for (int i = k / 2 + 1; i <= k; i++) {
					ans[i] = max({ans[i - 1], d1[i] + d2[k - i], d1[k - i] + d2[i]});
				}
				dp[i].clear();
				hap[i] = 0;
				for (int z = 1; z <= k; z++)
					if (ans[z] > ans[z - 1]) {
						dp[i].insert(-(ans[z] - ans[z - 1]));
						hap[i] += ans[z] - ans[z - 1];
					}
			} else {
				{
					vector<lint> deltas(all(dp[j]));
					auto it = dp[i].begin();
					vector<lint> topush;
					for (auto &x : deltas) {
						topush.push_back(x + *it);
						it = dp[i].erase(it);
					}
					for (auto &x : topush)
						dp[i].insert(x);
					hap[i] += hap[j];
				}
				{
					vector<lint> todo(k - sz(dp[i]));
					while (sz(dp[i]) > k - sz(dp[j])) {
						auto it = --dp[i].end();
						todo.push_back(-*it);
						hap[i] += *it;
						dp[i].erase(it);
					}
					reverse(all(todo));
					for (auto &x : todo) {
						dp[j].insert(-x);
						lint cur_increase = x + *dp[j].rbegin();
						if (cur_increase > 0)
							dp[i].insert(-cur_increase), hap[i] += cur_increase;
						else
							break;
						dp[j].erase(--dp[j].end());
					}
				}
			}
		}
		ans[i] = hap[i];
	}
	for (int i = 0; i < n; i++)
		cout << ans[i] << "\n";
}