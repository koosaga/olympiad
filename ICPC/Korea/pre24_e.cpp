#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> a(n, vector<int>(n));
	vector<vector<int>> b(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> b[i][j];
	}
	vector<int> ans(n);
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++)
			ans[j] = max(ans[j], abs(a[i][j] - b[i][j]));
	}
	lint dap = 0;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		dap += ans[--x];
	}
	cout << dap << "\n";
}