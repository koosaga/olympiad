#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }
lint dot(pi a, pi b) { return a[0] * b[0] + a[1] * b[1]; }
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	vector<lint> ans(n + 5);
	auto go = [&](vector<pi> &a) {
		vector<pi> b;
		for (int i = 0; i < 2; i++)
			b.insert(b.end(), all(a));
		int j = 0, k = 0;
		for (int i = 0; i < sz(a); i++) {
			j = max(j, i + 1);
			k = max(k, i + 1);
			while (j < sz(a) + i && ccw(b[i], b[j]) > 0)
				j++;
			while (k < j && dot(b[i], b[k]) > 0)
				k++;
			ans[k - i - 1]++;
			ans[j - i - 1]--;
		}
	};
	for (int i = 0; i < n; i++) {
		vector<pi> vect;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				vect.push_back({a[j][0] - a[i][0], a[j][1] - a[i][1]});
			}
		}
		sort(all(vect), [&](const pi &a, const pi &b) {
			bool m1 = (a < pi{0, 0});
			bool m2 = (b < pi{0, 0});
			if (m1 != m2)
				return m1 < m2;
			return ccw(a, b) > 0;
		});
		go(vect);
	}
	for (int i = 0; i <= n - 3; i++) {

		if (i)
			ans[i] += ans[i - 1];
		cout << ans[i] * 2 << "\n";
	}
}