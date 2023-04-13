#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k;
	cin >> k;
	vector<pi> ans(100, pi{-1, -1});
	// 99 - 2i = 2^i
	for (int i = 97; i >= 41; i -= 2) {
		ans[i] = {i + 1, i + 2};
		ans[i + 1] = {i + 2, -1};
	}
	vector<int> v;
	ans[0] = {1, -1};
	for (int i = 0; i < 30; i++) {
		if ((k >> i) & 1) {
			ans[i + 1] = {99 - 2 * i, i + 2};
		} else {
			ans[i + 1] = {i + 2, -1};
		}
	}
	cout << "100\n";
	for (auto &[x, y] : ans) {
		if (x >= 0)
			x++;
		if (y >= 0)
			y++;
		cout << x << " " << y << "\n";
	}
}