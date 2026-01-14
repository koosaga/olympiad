#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int mod = 1e9 + 7;

void solve() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<unsigned> dp(8 * n + 1);
	dp[0] = 1;
	for (int i = 1; i < sz(dp); i++) {
		unsigned r = dp[i - 1];
		if ((r & (1 << 31)) != 0)
			r = (r << 1) ^ 0x04c11db7;
		else
			r = (r << 1); // do some magic
		dp[i] = r;
	}
	unsigned ans = 0;
	for (int i = 0; i < 8 * n; i++) {
		if (s[i / 8] & 1 << (7 - i % 8))
			ans ^= dp[8 * n - 1 - i];
	}
	cout << ans << "\n";
	int q;
	cin >> q;
	while (q--) {
		int p;
		char c;
		cin >> p >> c;
		p--;
		for (int i = 8 * p; i < 8 * p + 8; i++) {
			if (s[i / 8] & 1 << (7 - i % 8))
				ans ^= dp[8 * n - 1 - i];
		}
		s[p] = c;
		for (int i = 8 * p; i < 8 * p + 8; i++) {
			if (s[i / 8] & 1 << (7 - i % 8))
				ans ^= dp[8 * n - 1 - i];
		}
		cout << ans << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--)
		solve();
}