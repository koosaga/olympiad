#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
typedef long long lint;

int n, a[MAXN], b[MAXN];
int dp[1005], nxt[1005];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++) {
		int r;
		cin >> r;
		b[r] = i;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		nxt[0] = 1e9;
		int baddy = b[a[i]];
		for (int j = 1; j < 1005; j++) {
			nxt[j] = min(dp[j - 1], dp[j] + 1 + (dp[j] + 1 == baddy));
		}
		nxt[0] = dp[0] + 1 + (dp[0] + 1 == baddy);
		memcpy(dp, nxt, sizeof(dp));
	}
	for (int i = 0; i < 1005; i++) {
		if (dp[i] <= n) {
			cout << n + i << "\n";
			return 0;
		}
	}
}
