#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, c;
	cin >> n >> c;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	vector<lint> ds(500005), dp(n);
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	lint mx = 0;
	auto upd = [&](int pos, lint val) {
		ds[pos] = max(ds[pos], val);
		mx = max(mx, val);
	};
	for (int i = 0; i < n;) {
		int j = i;
		while (j < n && a[i][0] == a[j][0]) {
			dp[j] = max(mx - c, ds[a[j][1]]) + a[j][0];
			j++;
		}
		for (int k = i; k < j; k++) {
			upd(a[k][1], dp[k]);
		}
		i = j;
	}
	cout << *max_element(all(dp)) << "\n";
}