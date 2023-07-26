#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using llf = long double;
const int MAXN = 505;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<string> str(2 * n + 1);
	for (int i = 0; i < 2 * n + 1; i++)
		cin >> str[i];
	vector<vector<int>> d[2];
	d[0].resize(n);
	d[1].resize(n);
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < n; i++) {
			d[j][i].resize(m);
			fill(all(d[j][i]), 1e9);
		}
	}
	pi src[2] = {{0, 0}, {n - 1, m - 1}};
	for (int i = 0; i < 2; i++) {
		queue<array<int, 3>> que;
		auto enq = [&](int x, int y, int dv) {
			if (d[i][x][y] > dv) {
				d[i][x][y] = dv;
				que.push({x, y, dv});
			}
		};
		enq(src[i][0], src[i][1], 0);
		while (sz(que)) {
			auto [x, y, d] = que.front();
			que.pop();
			if (str[2 * x + 1][2 * y + 2] == '.')
				enq(x, y + 1, d + 1);
			if (str[2 * x + 1][2 * y] == '.')
				enq(x, y - 1, d + 1);
			if (str[2 * x][2 * y + 1] == '.')
				enq(x - 1, y, d + 1);
			if (str[2 * x + 2][2 * y + 1] == '.')
				enq(x + 1, y, d + 1);
		}
	}
	int ans = d[0][n - 1][m - 1];
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			if (y + 1 < m && str[2 * x + 1][2 * y + 2] == '|') {
				int d11 = d[0][x][y], d12 = d[0][x][y + 1];
				int d21 = d[1][x][y], d22 = d[1][x][y + 1];
				if (d11 + d22 != d12 + d21) {
					ans = max(ans, min(d11 + d22, d12 + d21) + 1);
				}
			}
			if (x + 1 < n &&str[2 * x + 2][2 * y + 1] == '-') {
				int d11 = d[0][x][y], d12 = d[0][x + 1][y];
				int d21 = d[1][x][y], d22 = d[1][x + 1][y];
				if (d11 + d22 != d12 + d21) {
					ans = max(ans, min(d11 + d22, d12 + d21) + 1);
				}
			}
		}
	}
	cout << ans + 1 << "\n";
}