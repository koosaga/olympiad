#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<array<int, 4>>> gph(n);
	for (int i = 0; i < m; i++) {
		int a, b, c, d, k;
		cin >> a >> b >> c >> d >> k;
		a--;
		b--;
		c--;
		d--;
		gph[d].push_back({a, b, c, k});
	}
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		array<int, 4> cnt = {};
		for (auto &[p, q, r, s] : gph[i]) {
			int val = s - ans[p] - ans[q] - ans[r];
			val = (val % 4 + 4) % 4;
			cnt[val]++;
		}
		ans[i] = max_element(all(cnt)) - cnt.begin();
	}
	for (auto &x : ans)
		cout << x << " ";
}
