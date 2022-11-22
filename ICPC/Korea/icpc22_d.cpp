#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
	vector<lint> dp(n + 1, 1e18);
	dp[0] = 0;
	lint ret = 1e18;
	int posmax = 0;
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	for (int i = 1; i <= n; i++) {
		while (sz(pq) && pq.top().first <= a[i]) {
			posmax = max(posmax, pq.top().second);
			pq.pop();
		}
		dp[i] = a[i] - a[posmax];
		pq.emplace(dp[i] + a[i], i);
		ret = min(ret, max(dp[i], a[n] - a[i]));
	}
	cout << ret << "\n";
}