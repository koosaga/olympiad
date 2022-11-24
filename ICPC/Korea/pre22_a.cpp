#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int L = 0, R = 0;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (L <= R)
			L += x;
		else
			R += x;
	}
	int q = abs(R - L);
	vector<int> dp(q + 1, 1e9);
	dp[0] = 0;
	for (int i = 1; i <= q; i++) {
		for (auto &j : {1, 2, 5, 10, 20, 50, 100}) {
			if (j > i)
				break;
			dp[i] = min(dp[i], dp[i - j] + 1);
		}
	}
	cout << dp[q] << "\n";
}