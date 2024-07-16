#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> dp(5000005, 1e9);
	dp[0] = 0;
	int suma = 0;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		suma += a;
		for (int j = sz(dp) - 1; j >= a; j--)
			dp[j] = min(dp[j], dp[j - a] + b);
	}
	int ans = 1e9;
	for (int i = 0; i < sz(dp); i++)
		ans = min(ans, max(dp[i], suma - i));
	cout << ans << "\n";
}