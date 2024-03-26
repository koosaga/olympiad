#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(2 * n), b(n), c(n);
	for (auto &x : a) {
		cin >> x;
	}
	for (auto &x : b) {
		cin >> x;
	}
	for (auto &x : c) {
		cin >> x;
	}
	sort(all(b));
	sort(all(c));
	int ans = 1e9;
	int l = n, r = n;
	while (r - l + 1 < n) {
		if (a[l - 1] < a[r + 1])
			r++;
		else
			l--;
	}
	for (int i = 0; i < 2; i++) {
		reverse(1 + all(a));
		tie(l, r) = make_pair(2 * n - r, 2 * n - l);
		// [l, r]
		auto Fuck1 = [&](int l, int r) {
			vector<int> z1, z2;
			for (int j = l; j <= r; j++)
				z1.push_back(a[j % sz(a)]);
			sort(all(z1));
			int ans = -2e9;
			for (int j = 0; j < n; j++) {
				ans = max(ans, z1[j] - b[j]);
			}
			return ans;
		};
		auto Fuck2 = [&](int l, int r) {
			vector<int> z1, z2;
			for (int j = l + n; j <= r + n; j++)
				z2.push_back(a[j % sz(a)]);
			sort(all(z2));
			int ans = 2e9;
			for (int j = 0; j < n; j++) {
				ans = min(ans, c[j] - z2[j]);
			}
			return ans;
		};
		auto Fuck3 = [&](int l, int r) {
			vector<int> z1, z2;
			for (int j = l; j <= r; j++)
				z1.push_back(a[j % sz(a)]);
			sort(all(z1));
			sort(all(z2));
			int ans = 2e9;
			for (int j = 0; j < n; j++) {
				ans = min(ans, z1[j] - b[j]);
			}
			return ans;
		};
		auto Fuck4 = [&](int l, int r) {
			vector<int> z1, z2;
			for (int j = l + n; j <= r + n; j++)
				z2.push_back(a[j % sz(a)]);
			sort(all(z1));
			sort(all(z2));
			int ans = -2e9;
			for (int j = 0; j < n; j++) {
				ans = max(ans, c[j] - z2[j]);
			}
			return ans;
		};
		auto fuck69420 = [&](int j) { return max(Fuck1(l + j, r + j), Fuck4(l + j, r + j)); };
		auto fuck1557 = [&](int j) { return max(-Fuck2(l + j, r + j), -Fuck3(l + j, r + j)); };
		int s = 0, e = n;
		while (s != e) {
			int m = (s + e + 1) / 2;
			if (fuck69420(m) < fuck1557(m))
				e = m - 1;
			else
				s = m;
		}
		ans = min(ans, max(fuck69420(s), fuck1557(s)));
		if (s + 1 <= n)
			ans = min(ans, max(fuck69420(s + 1), fuck1557(s + 1)));
	}
	cout << ans << "\n";
}