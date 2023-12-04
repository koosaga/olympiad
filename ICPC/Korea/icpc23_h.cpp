#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i][1];
	}
	sort(all(a));
	vector<int> dp(n);
	for (int i = 0; i < n; i++) {
		ans += max(a[i][0], a[i][1]);
		for (int j = 0; j < i; j++) {
			if (a[j][1] < a[i][1])
				dp[i] = max(dp[i], dp[j]);
		}
		dp[i] += min(a[i][0], a[i][1]);
	}
	cout << *max_element(all(dp)) + ans << "\n";
}