#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int MAXN = 2005;

int n, m;
char str[MAXN][MAXN];
bool L[MAXN][MAXN], R[MAXN][MAXN];

void dfs(int x, int y) {
	str[x][y] = '.';
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i + x < 0 || j + y < 0 || i + x > n + 1 || j + y > m + 1)
				continue;
			if (str[i + x][j + y] == '#')
				dfs(i + x, j + y);
		}
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i <= m + 1; i++)
		str[0][i] = str[n + 1][i] = '#';
	for (int i = 1; i <= n; i++) {
		string fuck;
		cin >> fuck;
		for (int j = 1; j <= m; j++)
			str[i][j] = fuck[j - 1];
		str[i][0] = str[i][m + 1] = '#';
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == 1 && j == 1)
				L[i][j] = 1;
			else if (str[i][j] != '#')
				L[i][j] = L[i - 1][j] | L[i][j - 1];
		}
	}
	for (int i = n; i; i--) {
		for (int j = m; j; j--) {
			if (i == n && j == m)
				R[i][j] = 1;
			else if (str[i][j] != '#') {
				R[i][j] = R[i + 1][j] | R[i][j + 1];
			}
		}
	}
	if (R[1][1] == 0) {
		cout << "0\n";
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!L[i][j] || !R[i][j])
				str[i][j] = '#';
		}
	}
	int cnt = 0;
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= m + 1; j++) {
			if (str[i][j] == '#')
				dfs(i, j), cnt++;
		}
	}
	cout << cnt << "\n";
}