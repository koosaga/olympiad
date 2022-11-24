#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int dp[41][101][101][101];

int f(int t, int a, int b, int c) {
	if (a + b + c == 0)
		return 0;
	if (~dp[t][a][b][c])
		return dp[t][a][b][c];
	int ans = -1e9;
	if (a)
		ans = max(ans, min(a, t) - f(t + 1, max(a - t, 0), b, c));
	if (b)
		ans = max(ans, min(b, t) - f(t + 1, a, max(b - t, 0), c));
	if (c)
		ans = max(ans, min(c, t) - f(t + 1, a, b, max(c - t, 0)));

	return dp[t][a][b][c] = ans;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int a, b, c;
	cin >> a >> b >> c;
	memset(dp, -1, sizeof(dp));
	int ans = f(1, a, b, c);
	if (ans > 0)
		cout << "F";
	else if (ans == 0)
		cout << "D";
	else
		cout << "S";
	cout << "\n";
}