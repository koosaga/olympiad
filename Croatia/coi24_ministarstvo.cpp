#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n, vector<int>(n));
	for (auto &x : adj)
		for (auto &y : x)
			cin >> y;
	pi ans{-1, 0};
	for (int i = 0; i < n; i++) {
		int outdeg = count(all(adj[i]), 1);
		if (outdeg == n - 1) {
			cout << "-1\n";
			return 0;
		}
		ans = max(ans, pi{outdeg, i});
	}
	cout << "3\n";
	int v = ans[1];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adj[i][j]) {
				if (adj[v][i] && adj[v][j])
					adj[i][j] = 2;
				if (adj[i][v] && adj[j][v])
					adj[i][j] = 2;
				if (j == v)
					adj[i][j] = 2;
				if (adj[v][i] && adj[j][v])
					adj[i][j] = 3;
			}
			cout << adj[i][j] << " ";
		}
		cout << "\n";
	}
}