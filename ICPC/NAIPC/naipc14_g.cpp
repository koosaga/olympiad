
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
	int n;
	while (cin >> n) {

		if (n == 0)
			break;

		int ans = 0;

		for (int i = 1; i * i <= 2 * n; i++) {

			if (i % 2 == 1) {

				if (n % i != 0)
					continue;

				if (n / i - i / 2 > 1)
					ans++;

			} else {

				if (n % (i / 2) != 0)
					continue;

				int avg = n / (i / 2);

				if (avg % 2 == 0)
					continue;

				if (avg / 2 - i / 2 >= 1)
					ans++;
			}
		}

		cout << ans << '\n';
	}
}