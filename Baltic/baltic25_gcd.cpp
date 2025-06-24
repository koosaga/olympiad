#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	vector<pi> dp;
	dp.push_back({0, 0});
	for (auto &x : a) {
		vector<pi> nxt;
		for (int d = 0; d <= 11; d++) {
			for (auto &[y, w] : dp) {
				if (w + d <= 11)
					nxt.push_back({gcd(y, d + x), w + d});
			}
		}
		sort(all(nxt));
		dp.clear();
		for (int j = 0; j < sz(nxt); j++) {
			if (j == 0 || nxt[j - 1][0] != nxt[j][0])
				dp.push_back(nxt[j]);
		}
	}
	cout << dp[0][1] << "\n";
}