#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 200005;

vector<pi> seq;

void dfs(int n, int x, int y, vector<vector<int>> &a, vector<vector<int>> &ans) {
	seq.push_back({x, y});
	for (int k = 0; k < n; k++) {
		if (a[y][k] == 1 && a[x][k] == 0 && ans[k][y] == 0) {
			ans[k][y] = 1;
			ans[y][k] = -1;
			dfs(n, k, y, a, ans);
		}
		if (a[x][k] == 1 && a[y][k] == 0 && ans[x][k] == 0) {
			ans[x][k] = 1;
			ans[k][x] = -1;
			dfs(n, x, k, a, ans);
		}
	}
}

vector<vector<int>> order(int n, vector<vector<int>> a) {
	vector<vector<int>> ans(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j]) {
				ans[i][j] = 1;
				ans[j][i] = -1;
				dfs(n, i, j, a, ans);
				for (auto &[x, y] : seq)
					a[x][y] = 0;
				seq.clear();
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (ans[i][j] == 1 && ans[j][k] == 1 && ans[i][k] != 1) {
					return vector<vector<int>>();
				}
			}
		}
	}
	return ans;
}

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
	auto O1 = order(n, a);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j)
				a[i][j] ^= 1;
		}
	}
	auto O2 = order(n, a);
	if (sz(O1) == 0 || sz(O2) == 0) {
		cout << "NO\n";
		return 0;
	}
	vector<int> ans[2];
	for (int i = 0; i < 2; i++) {
		ans[i].resize(n);
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (O1[j][k] == 1 || O2[j][k] == 1 - 2 * i)
					ans[i][k]++;
			}
		}
	}
	cout << "YES\n";
	for (auto &x : ans[0])
		cout << x + 1 << " ";
	cout << "\n";
	for (auto &x : ans[1])
		cout << x + 1 << " ";
	cout << "\n";
}