#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;
const int MAXN = 2005;

int dp[MAXN][2 * MAXN][3];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	string s[2], t[2];
	cin >> n;
	vector<int> v;
	for (int i = 0; i < 2; i++) {
		cin >> s[i];
		for (int j = 0; j < n; j++) {
			if (s[i][j] == 'o')
				v.push_back(j);
		}
	}
	sort(all(v));
	for (int i = 0; i < 2; i++)
		cin >> t[i];
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][0] = 0;
	auto match = [&](char c, int x) {
		if (c == '*')
			return true;
		if (c == 'o')
			return x == 1;
		return x == 0;
	};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= sz(v); j++) {
			for (int a = 0; a < 2; a++) {
				for (int b = 0; b < 2; b++) {
					if (!match(t[0][i], a) || !match(t[1][i], b))
						continue;
					if (a + b == 0) {
						for (int k = 0; k < 3; k++) {
							dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][k]);
						}
					} else if (a + b == 1) {
						if (j + 1 <= sz(v)) {
							int d = abs(v[j] - i);
							int from = (s[0][i] == 'o') + (s[1][i] == 'o') * 2;
							int to = a + b * 2;
							if (d == 0 && from + to == 3) {
								for (int k = 0; k < 3; k++) {
									if (from + k == 3) {
										dp[i + 1][j + 1][0] = min(dp[i + 1][j + 1][0], dp[i][j][k]);
									} else {
										dp[i + 1][j + 1][from] = min(dp[i + 1][j + 1][from], dp[i][j][k] + 1);
									}
								}
							} else {
								for (int k = 0; k < 3; k++) {
									dp[i + 1][j + 1][0] = min(dp[i + 1][j + 1][0], dp[i][j][k] + d);
								}
							}
						}
					} else {
						if (j + 2 <= sz(v)) {
							for (int k = 0; k < 3; k++) {
								dp[i + 1][j + 2][0] = min(dp[i + 1][j + 2][0], dp[i][j][k] + abs(v[j] - i) + abs(v[j + 1] - i));
							}
						}
					}
				}
			}
		}
	}
	cout << *min_element(dp[n][sz(v)], dp[n][sz(v)] + 3) << "\n";
}