#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int offset = 10;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s, t;
	cin >> s;
	t = s;
	reverse(all(t));
	int dp[MAXN][2 * offset + 5] = {};
	for (int i = 0; i < sz(s); i++) {
		for (int j = -offset + 1; j <= offset - 1; j++) {
			int k = i + j;
			if (k < 0 || k >= sz(t))
				continue;
			dp[i + 1][j + offset] = max({dp[i + 1][j + offset - 1], dp[i][j + offset + 1], dp[i][j + offset] + (t[k] == s[i])});
		}
	}
	int ans = sz(s) - dp[sz(s)][offset];
	if (ans >= 4)
		ans = -1;
	cout << ans << "\n";
}