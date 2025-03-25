#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

void fuck() {
	cout << "9\n";
	int R = 8;
	int n = 48;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\n";
		vector<string> s(R + 2, string(n, 'F'));
		s[0][i] = 'T';
		vector<vector<pair<char, int>>> ans(n, vector<pair<char, int>>(R + 1));
		for (int m = 0; m < R / 2; m++) {
			for (int j = 0; j < n; j++) {
				ans[j][m].first = s[m][j];
				ans[j][m].second = j ^ (1 << m);
			}
			for (int j = 0; j < n; j++) {
				s[m + 1][j] = s[m][j];
				if (s[m][ans[j][m].second] == 'T')
					s[m + 1][j] = 'T';
			}
		}
		for (int j = 0; j < n; j++) {
			if (s[R / 2][j] == 'F') {
				ans[j][R / 2].first = 'F';
				ans[j][R / 2].second = (j + 16) % n;
			} else {
				ans[j][R / 2].first = 'T';
				ans[j][R / 2].second = j;
			}
		}
		cerr << "dbg" << s[R / 2] << endl;
		for (int m = R / 2 + 1; m <= R; m++) {
			if (m == R / 2 + 1) {
				for (int j = 0; j < n; j++) {
					ans[j][m].first = s[R - m][j];
					if (s[R / 2][j] == 'F' && s[R / 2][ans[j][R / 2].second] == 'F') {
						ans[j][R / 2 + 1].second = (j + 32) % n;
					} else
						ans[j][R / 2 + 1].second = ans[j][R / 2].second;
				}
			} else {
				for (int j = 0; j < n; j++) {
					ans[j][m].first = s[R - m][j];
					if (s[m][ans[j][m - 1].second] == 'F') {
						ans[j][m].second = ans[j][m - 1].second ^ (1 << (R - m + 1));
					} else {
						ans[j][m].second = ans[j][m - 1].second;
					}
				}
			}
			for (int j = 0; j < n; j++) {
				s[m + 1][j] = s[R + 1 - (m + 1)][j];
			}
		}
		for (int j = 0; j < n; j++) {
			for (int k = 0; k <= R; k++) {
				cout << ans[j][k].first << " " << ans[j][k].second + 1 << " ";
			}
			cout << "\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	if (n == 48) {
		fuck();
		return 0;
	}
	int k = 0;
	while ((1 << k) < n)
		k++;
	int R = 2 * k - 2;
	cout << R << "\n";
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\n";
		vector<string> s(R + 1, string(n, 'F'));
		s[0][i] = 'T';
		vector<vector<pair<char, int>>> ans(n, vector<pair<char, int>>(R));
		for (int m = 0; m < R / 2; m++) {
			for (int j = 0; j < n; j++) {
				ans[j][m].first = s[m][j];
				ans[j][m].second = j ^ (1 << m);
			}
			for (int j = 0; j < n; j++) {
				s[m + 1][j] = s[m][j];
				if (s[m][ans[j][m].second] == 'T')
					s[m + 1][j] = 'T';
			}
		}
		for (int m = R / 2; m < R; m++) {
			if (m == R / 2) {
				for (int j = 0; j < n; j++) {
					if (s[R / 2][j] == 'F') {
						ans[j][R / 2].first = 'F';
						ans[j][R / 2].second = j ^ (1 << (R / 2));
					} else {
						ans[j][R / 2].first = s[R / 2 - 1][j];
						ans[j][R / 2].second = j;
					}
				}
			} else {
				for (int j = 0; j < n; j++) {
					ans[j][m].first = s[R - 1 - m][j];
					if (s[m][ans[j][m - 1].second] == 'F') {
						ans[j][m].second = ans[j][m - 1].second ^ (1 << (R - m));
					} else {
						ans[j][m].second = ans[j][m - 1].second;
					}
				}
			}
			for (int j = 0; j < n; j++) {
				s[m + 1][j] = s[R - m - 1][j];
			}
		}
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < R; k++) {
				cout << ans[j][k].first << " " << ans[j][k].second + 1 << " ";
			}
			cout << "\n";
		}
	}
}