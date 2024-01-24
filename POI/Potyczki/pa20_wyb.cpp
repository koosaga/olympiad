#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 1005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int cnt[6][3] = {};
	int n;
	cin >> n;
	while (n--) {
		string s;
		cin >> s;
		cnt[s[0] - '0'][s[1] - 'A']++;
	}
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (cnt[i][j] == 0) {
				cout << "NIE\n";
				return 0;
			}
		}
	}
	for (int j = 0; j < 3; j++) {
		if (cnt[5][j] == 0) {
			cout << "NIE\n";
			return 0;
		}
	}
	cout << "TAK\n";
}