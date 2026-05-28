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
	string s;
	cin >> s;
	vector<lint> dp(sz(s) + 1);
	dp[0] = 1;
	for (int i = 0; i < sz(s); i++) {
		dp[i + 1] += dp[i] * (s[i] - '0' + 1);
		if (i + 2 <= sz(s) && s[i] == '1') {
			dp[i + 2] += dp[i] * ('9' - s[i + 1]);
		}
	}
	cout << dp.back() << "\n";
}