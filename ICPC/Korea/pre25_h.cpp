#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y;
	sort(all(a), [&](const pi &a, const pi &b) { return pi{a[0] - a[1], -a[1]} < pi{b[0] - b[1], -b[1]}; });
	vector<int> dp;
	for (auto &[x, y] : a) {
		auto it = lower_bound(all(dp), x + y);
		if (it == dp.end())
			dp.push_back(x + y);
		else
			*it = x + y;
	}
	cout << sz(dp) << "\n";
}