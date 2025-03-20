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
	int n;
	cin >> n;
	lint ans = 0;
	vector<int> cnt(n * n + 1);
	for (int a = 1; a <= n; a++) {
		for (int b = 1; b <= a && a * a + b * b <= n * n; b++) {
			cnt[a * a + b * b]++;
		}
	}
	for (int d = 1; d <= n; d++) {
		for (int c = 1; c < d; c++) {
			ans += cnt[d * d - c * c];
		}
	}
	cout << ans << "\n";
}