#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		auto ok = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; };
		vector<vector<int>> a(n, vector<int>(m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> a[i][j];
			}
		}
		auto greedy = [&](int i, int j) {
			if (a[i][j])
				return;
			set<int> S;
			for (int k = 0; k < 4; k++)
				if (ok(i + dx[k], j + dy[k]))
					S.insert(a[i + dx[k]][j + dy[k]]);
			S.insert(0);
			while (S.count(a[i][j]) && a[i][j] < 4)
				a[i][j]++;
		};
		for (int i = n - 1; i >= 0; i--) {
			for (int j = m - 1; j >= 0; j--) {
				if (1 <= i && i <= 3 && 1 <= j && j <= 3)
					continue;
				greedy(i, j);
			}
		}
		a[2][2] = a[0][2];
		greedy(1, 1);
		greedy(2, 1);
		greedy(3, 1);
		greedy(3, 2);
		greedy(3, 3);
		greedy(2, 3);
		greedy(1, 3);
		greedy(1, 2);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << a[i][j] << " ";
			}
			cout << "\n";
		}
	}
}