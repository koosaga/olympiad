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
	int n, w;
	cin >> n >> w;
	for (int x = 4; x <= w; x++) {
		vector<int> v;
		vector<vector<int>> ans;
		for (int i = 0; i < x / 2; i++)
			v.push_back(1);
		for (int i = x / 2; i < x; i++)
			v.push_back(2);
		while (v[0] == 1 && sz(ans) < n) {
			ans.push_back(v);
			next_permutation(all(v));
		}
		if (sz(ans) == n) {
			cout << x << "\n";
			for (int i = 0; i < w; i++) {
				for (int j = 0; j < n; j++)
					cout << ans[j][i % x];
				cout << "\n";
			}
			return 0;
		}
	}
	cout << "infinity\n";
}