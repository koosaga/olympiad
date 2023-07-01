#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct interval {
	lint s, e, x;
};

bool cmp1(const interval &a, const interval &b) { return a.s < b.s; }
bool cmp2(const interval &a, const interval &b) { return a.e < b.e; }

const int MAXN = 600005;
lint dp[2][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<interval> cont[2];
	int cnt = 0;
	for (int i = 0; i < n + m; i++) {
		interval a;
		cin >> a.s >> a.e;
		if (i < n && a.s == 0) {
			cnt++;
			continue;
		}
		a.x = (i >= n);
		cont[i >= n].push_back(a);
	}
	sort(all(cont[0]), cmp1);
	sort(all(cont[1]), cmp1);
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	auto get_end = [&](int j, lint t) {
		auto it = upper_bound(all(cont[j]), interval{0, t, 0}, cmp2);
		if (it == cont[j].end() || it->s > t)
			return -1ll;
		return it->e;
	};
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < 2; j++) {
			if (dp[j][i] > 1e17)
				continue;
			//	cout << j << " " << i << " " << dp[j][i] << endl;
			{
				lint arrival = dp[j][i] + k;							 // arrival + e
				lint no_return = max(arrival, get_end(j, dp[j][i]) - k); // no_return + e
				int it1 = upper_bound(all(cont[j ^ 1]), interval{-1, arrival, -1}, cmp2) - cont[j ^ 1].begin();
				int it2 = upper_bound(all(cont[j ^ 1]), interval{no_return, -1, -1}, cmp1) - cont[j ^ 1].begin();
				int x = it2 - it1;
				dp[j ^ 1][i + x] = min(dp[j ^ 1][i + x], no_return);
			}
		}
		for (int j = 0; j < 2; j++) {
			if (dp[j][i] > 1e17)
				continue;
			auto it1 = upper_bound(all(cont[j]), interval{dp[j][i], -1, -1}, cmp1);
			if (it1 != cont[j].end())
				dp[j][i + 1] = min(dp[j][i + 1], it1->s);
		}
	}
	for (int i = MAXN - 1;; i--) {
		if (dp[0][i] < 1e17 || dp[1][i] < 1e17) {
			cout << i + cnt << "\n";
			return 0;
		}
	}
}