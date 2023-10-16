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
	int tot = 0;
	vector<array<int, 3>> g1, g2;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int sum = 0, nd = 0;
		for (auto &ch : s) {
			if (ch == '(')
				sum++;
			else
				sum--;
			nd = max(nd, -sum);
		}
		sum += nd;
		if (nd <= sum)
			g1.push_back({nd, sum, i + 1});
		else
			g2.push_back({nd, sum, i + 1});
		tot += sum - nd;
	}
	if (tot != 0) {
		cout << "impossible\n";
		return 0;
	}
	sort(all(g1), [&](array<int, 3> a, array<int, 3> b) { return a < b; });
	sort(all(g2), [&](array<int, 3> a, array<int, 3> b) { return a[1] > b[1]; });
	int sum = 0;
	for (auto &x : g1) {
		sum -= x[0];
		if (sum < 0) {
			cout << "impossible\n";
			return 0;
		}
		sum += x[1];
	}
	for (auto &x : g2) {
		sum -= x[0];
		if (sum < 0) {
			cout << "impossible\n";
			return 0;
		}
		sum += x[1];
	}
	for (auto &x : g1)
		cout << x[2] << "\n";
	for (auto &x : g2)
		cout << x[2] << "\n";
}