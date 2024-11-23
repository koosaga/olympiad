#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1000005;

int a[3][MAXN];
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	int cnt[2][26] = {};
	for (int i = 0; i < 2; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < n; j++) {
			cnt[j % 2][s[j] - 'a'] += 2 * i - 1;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 26; j++) {
			if (cnt[i][j]) {
				cout << "No\n";
				return 0;
			}
		}
	}
	cout << "Yes\n";
}