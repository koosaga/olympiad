#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;

lint sum(lint l, lint r) { return (r - l + 1) * (r + l) / 2; }

vector<int> knap(lint n, lint h) {
	// h with 1, 3, ..., 2n-1
	for (int t = 0; t <= n; t++) {
		if (h - t >= 2 * sum(0, t - 1) && h - t <= 2 * sum(n - t, n - 1) && h % 2 == t % 2) {
			vector<int> ans(t);
			iota(all(ans), 0);
			lint q = h - t - 2 * sum(0, t - 1);
			q /= 2;
			for (int j = t - 1; j >= 0; j--) {
				int d = min(q, n - t);
				ans[j] += d;
				q -= d;
			}
			for (auto &x : ans)
				x = 2 * x + 1;
			return ans;
		}
	}
	cout << n << " " << h << endl;
	assert(0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint n, h;
	cin >> n >> h;
	if (h < 2 * n - 1 || h > n * n) {
		cout << "impossible\n";
		return 0;
	}
	if (h == n * n - 2) {
		cout << "impossible\n";
		return 0;
	}
	if (h == 2 * n + 1) {
		vector<lint> ans = {2 * n - 1, 3, 1};
		for (int j = 2 * n - 3; j >= 5; j -= 2)
			ans.push_back(j);
		for (auto &x : ans)
			cout << x << " ";
		return 0;
	}
	h -= 2 * n - 1;
	auto z = knap(n - 1, h);
	sort(all(z));
	for (auto &p : z) {
		cout << p << " ";
	}
	cout << 2 * n - 1 << " ";
	for (int j = 2 * n - 3; j >= 1; j -= 2) {
		if (!binary_search(all(z), j))
			cout << j << " ";
	}
}