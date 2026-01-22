#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int c[2] = {int(1e9), int(1e9)};
		for (int i = 0; i < 3; i++) {
			string s;
			cin >> s;
			for (int j = 0; j < 2; j++) {
				c[j] = min(c[j], (int)count(all(s), j + '0'));
			}
		}
		cout << max(c[0], c[1]) << "\n";
	}
}