#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 28;

char str[2][MAXN][MAXN];
int dp[2][MAXN][MAXN][MAXN][MAXN];

int f(int p, int sx, int ex, int sy, int ey) {
	if (sx > ex || sy > ey)
		return 0;
	if (~dp[p][sx][ex][sy][ey])
		return dp[p][sx][ex][sy][ey];
	unordered_set<int> s;
	for (int i = sx; i <= ex; i++) {
		for (int j = sy; j <= ey; j++) {
			if (str[p][i][j] == '.')
				continue;
			if (str[p][i][j] == 'R') {
				int l = f(p, sx, i - 1, sy, ey);
				int r = f(p, i + 1, ex, sy, ey);
				s.insert(l ^ r);
			}
			if (str[p][i][j] == 'B') {
				int l = f(p, sx, ex, sy, j - 1);
				int r = f(p, sx, ex, j + 1, ey);
				s.insert(l ^ r);
			}
			if (str[p][i][j] == 'G') {
				int a = f(p, sx, i - 1, sy, j - 1);
				int b = f(p, sx, i - 1, j + 1, ey);
				int c = f(p, i + 1, ex, sy, j - 1);
				int d = f(p, i + 1, ex, j + 1, ey);
				s.insert(a ^ b ^ c ^ d);
			}
		}
	}
	for (int i = 0;; i++) {
		if (s.count(i) == 0) {
			return dp[p][sx][ex][sy][ey] = i;
		}
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			str[0][i][j] = str[1][i][j] = '.';
		}
	}
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) {
			str[(i + j) % 2][(i + j) / 2][(i - j + m - 1) / 2] = s[j];
		}
	}
	for (int i = 0; i < 26; i++) {
		//	cout << str[0][i] << endl;
	}
	for (int i = 0; i < 26; i++) {
		//	cout << str[1][i] << endl;
	}

	memset(dp, -1, sizeof(dp));
	int ans = f(0, 0, 25, 0, 25) ^ f(1, 0, 25, 0, 25);
	if (ans)
		cout << "W\n";
	else
		cout << "L\n";
}