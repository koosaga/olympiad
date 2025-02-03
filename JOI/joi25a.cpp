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
	vector<int> a(n), b(n);
	map<lint, lint> mp;
	for (auto &x : a)
		cin >> x;
	for (auto &x : b)
		cin >> x, mp[x]++;
	for (int i = 1; i < n; i++)
		mp[a[i]]++;
	for (int i = 2; i < n; i++) {
		a[i] = max(a[i], a[i - 1]);
		b[i] = max(b[i], b[i - 1]);
	}
	a.erase(a.begin());
	b.erase(b.begin());
	n--;
	for (int i = 0; i < n; i++) {
		int j = lower_bound(all(b), a[i]) - b.begin();
		mp[a[i]] += j;
	}
	for (int i = 0; i < n; i++) {
		int j = upper_bound(all(a), b[i]) - a.begin();
		mp[b[i]] += j;
	}
	pi ans{0, 0};
	for (auto &[k, v] : mp) {
		ans = max(ans, pi{v, k});
	}
	cout << ans[1] << " " << ans[0] << "\n";
}