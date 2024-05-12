#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
		lint sum = 0;
	vector<vector<int>> dp(n + 1, vector<int>(n + 1));
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			if (a[i] <= a[j])
				dp[i][j] = dp[i + 1][j + 1] + 1;
			else
				dp[i][j] = 0;
				sum += dp[i][j];
		}
	}
	cout << sum << "\n";
}