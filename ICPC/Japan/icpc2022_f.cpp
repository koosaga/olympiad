#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;
int dp[2][MAXN], nxt[2][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	int sum = accumulate(all(a), 0);
	if (n % 2 || sum % 2) {
		cout << "No\n";
		return 0;
	}
	dp[0][0] = 1;
	int cur = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k <= cur; k++) {
				nxt[j][k] += dp[j][k];
				nxt[j ^ 1][k + a[i]] += dp[j][k];
			}
		}
		cur += a[i];
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k <= cur; k++) {
				dp[j][k] = min(4, nxt[j][k]);
				nxt[j][k] = 0;
			}
		}
	}
	cout << (dp[0][sum / 2] == 4 ? "Yes" : "No") << "\n";
}