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
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			bool ans = (i == 0 && j == 0);
			if (i && j) {
				if (i % 2 == 1)
					ans = 1;
				else if (j == 99)
					ans = 1;
			}
			cout << ans;
		}
		cout << "\n";
	}
}