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
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		y = -y;
		a[i] = {x + y, y - x};
	}
	sort(all(a), [&](const pi &a, const pi &b) { return pi{a[0], a[1]} < pi{b[0], b[1]}; });
	int ymin = 2.1e9;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (a[i][1] < ymin) {
			ymin = a[i][1];
			cnt++;
		}
	}
	cout << cnt << "\n";
}
