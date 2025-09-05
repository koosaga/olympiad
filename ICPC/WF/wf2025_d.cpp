#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

string buf = "NESW";
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<string> a(n);
	for (auto &s : a)
		cin >> s;
	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] == 'S')
				x = i, y = j;
		}
	}
	string s;
	cin >> s;

	int ans = 0;
	auto ok = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < m && a[x][y] != '#'; };
	auto cyc = [&](vector<vector<int>> adj) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					adj[j][k] |= (adj[j][i] & adj[i][k]);
				}
			}
		}
		for (int i = 0; i < 4; i++)
			if (adj[i][i])
				return true;
		return false;
	};
	vector<vector<int>> adj(4, vector<int>(4));
	for (auto &ch : s) {
		auto nxt = adj;
		int p = find(all(buf), ch) - buf.begin();
		for (int j = 0; j < 4; j++) {
			if (ok(x + dx[j], y + dy[j]) && j != p) {
				nxt[j][p] = 1;
			}
		}
		if (cyc(nxt)) {
			vector<vector<int>> ad2j(4, vector<int>(4));
			for (int j = 0; j < 4; j++) {
				if (ok(x + dx[j], y + dy[j]) && j != p) {
					ad2j[j][p] = 1;
				}
			}
			ans++;
			adj = ad2j;
		} else
			adj = nxt;
		x += dx[p];
		y += dy[p];
	}
	cout << ans << "\n";
}