#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n), ans;
	for (auto &[x, y] : a)
		cin >> x >> y;
	a.insert(a.begin(), {0, 0});
	for (int i = n; i >= 1;) {
		int j = i;
		while (j > 0 && a[i][1] - a[j][0] > 2 * (a[j][0] - a[j - 1][1])) {
			j--;
		}
		if (a[i][1] - a[j][0] > 2 * (a[j][0] - a[j - 1][1])) {
			cout << "impossible\n";
			return 0;
		}
		lint m = min(a[j][0], (a[j - 1][1] + a[i][1]) / 2);
		ans.push_back({a[j - 1][1], m});
		i = j - 1;
	}
	reverse(all(ans));
	cout << sz(ans) << "\n";
	for (auto &[x, y] : ans)
		cout << x << " " << y << "\n";
}