#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
const int MAXN = 5005;
using lint = long long;
using pi = array<lint, 2>;

lint dp[MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, t;
	cin >> n >> t;
	vector<pi> a;
	a.push_back({0, 0});
	a.push_back({t, 1});
	for (int i = 0; i < n; i++) {
		string s;
		lint x;
		cin >> s >> x;
		a.push_back({2 * t + x, s[0] - 'A'});
	}
	a.push_back({lint(1e18), 0});
	a.push_back({lint(1e18) + t, 1});
	sort(all(a));
	memset(dp, 0x3f, sizeof(dp));
	dp[0][1] = 0;
	for (int i = 1; i < sz(a); i++) {
		// dp[j, i] = ended at exactly i, different queue is finished till j
		lint cur = 2e18;
		for (int j = 0; j < i; j++) {
			if (a[i][1] != a[j][1]) {
				cur += a[i][0] + t - a[j][0];
			}
			cur = min(cur, dp[j][i]);
		}
		int oni = i;
		while (a[oni][1] == a[i][1])
			oni--;

		for (int j = i + 1; j < sz(a); j++) {
			if (a[i][1] == a[j][1])
				dp[oni][j] = min(dp[oni][j], dp[oni][i]);
		}
		{
			lint new_cur = cur;
			int ni = i;
			queue<int> whenGood[2];
			for (int j = i + 1; j < sz(a); j++) {
				if (a[i][1] != a[j][1] && a[j][0] >= a[i][0] + t) {
					lint ti = (a[j][0] - a[i][0]) / t;
					lint opp_finish = a[i][0] + (ti % 2 ? (ti - 1) : (ti - 2)) * t;
					while (sz(whenGood[a[i][1]]) && a[whenGood[a[i][1]].front()][0] <= opp_finish) {
						int k = whenGood[a[i][1]].front();
						whenGood[a[i][1]].pop();
						ni = k;
						lint delta = (opp_finish - a[k][0]) % (2 * t);
						new_cur += delta;
					}
					while (sz(whenGood[1 - a[i][1]]) && a[whenGood[1 - a[i][1]].front()][0] <= opp_finish + t) {
						int k = whenGood[1 - a[i][1]].front();
						whenGood[1 - a[i][1]].pop();
						lint delta = (opp_finish + t - a[k][0]) % (2 * t);
						new_cur += delta;
					}
					dp[ni][j] = min(dp[ni][j], new_cur);
				}
				whenGood[a[j][1]].push(j);
			}
		}
		{
			lint new_cur = cur;
			int ni = oni;
			queue<int> whenGood[2];
			for (int j = i + 1; j < sz(a); j++) {
				if (a[i][1] == a[j][1] && a[j][0] >= a[i][0] + 2 * t) {
					lint ti = (a[j][0] - a[i][0]) / t;
					lint opp_finish = a[i][0] + (ti % 2 ? (ti - 2) : (ti - 1)) * t;
					while (sz(whenGood[1 - a[i][1]]) && a[whenGood[1 - a[i][1]].front()][0] <= opp_finish) {
						int k = whenGood[1 - a[i][1]].front();
						whenGood[1 - a[i][1]].pop();
						ni = k;
						lint delta = (opp_finish - a[k][0]) % (2 * t);
						new_cur += delta;
					}
					while (sz(whenGood[a[i][1]]) && a[whenGood[a[i][1]].front()][0] <= opp_finish + t) {
						int k = whenGood[a[i][1]].front();
						whenGood[a[i][1]].pop();
						lint delta = (opp_finish + t - a[k][0]) % (2 * t);
						new_cur += delta;
					}
					dp[ni][j] = min(dp[ni][j], new_cur);
				}
				whenGood[a[j][1]].push(j);
			}
		}
	}
	cout << dp[sz(a) - 2][sz(a) - 1] << "\n";
}