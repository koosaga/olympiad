#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	map<int, pi> mp;
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		mp[b - c][a - 1]++;
	}
	int ans = 0;
	for (auto &[a, b] : mp)
		ans += min(b[0], b[1]);
	cout << ans << "\n";
}