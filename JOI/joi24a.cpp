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
	int n, t;
	cin >> n >> t;
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
		x %= t;
	}
	sort(all(a));
	int g = 0;
	for (int i = 0; i < n - 1; i++)
		g = max(g, a[i + 1] - a[i]);
	g = max(g, a[0] - a[n - 1] + t);
	cout << (t - g + 1) / 2 << "\n";
}