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
	vector<vector<int>> a(n, vector<int>(n));
	for (auto &x : a)
		for (auto &y : x)
			cin >> y;
	vector<array<int, 3>> ans;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			bool ok = 1;
			for (int k = 0; k < n; k++) {
				if (k != i && k != j && a[i][j] == a[i][k] + a[k][j])
					ok = 0;
				if (a[i][j] > a[i][k] + a[k][j]) {
					cout << "-1\n";
					return 0;
				}
			}
			if (ok) {
				ans.push_back({i + 1, j + 1, a[i][j]});
			}
		}
	}
	cout << sz(ans) << "\n";
	for (auto &[u, v, w] : ans)
		cout << u << " " << v << " " << w << "\n";
}