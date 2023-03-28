#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int n;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint r, c;
	cin >> r >> c;
	vector<lint> ret = {lint(1e18)};
	for (int i = 0; i < c; i++) {
		lint x = 0, y = 0, c1 = 0, c2 = 0;
		while (true) {
			c1++;
			lint nx = (y + i * r) % c;
			lint ny = (y + i * r) / c;
			if (x == nx && y == ny)
				break;
			x = nx, y = ny;
		}
		if ((y > 0 && x == 0) || (y < r - 1 && x == c - 1))
			continue;
		{
			lint x2 = c - 1, y2 = r - 1;
			while (true) {
				if (x2 == x && y2 == y)
					break;
				c2++;
				lint nx = (y2 + i * r) % c;
				lint ny = (y2 + i * r) / c;
				x2 = nx, y2 = ny;
			}
		}
		lint d = min(abs((c - 1) / 2 - x), abs(c / 2 - x)) + min(abs((r - 1) / 2 - y), abs(r / 2 - y));
		vector<lint> cur{d, i + 1, y + 1, x + 1, max(c1 - 1, c2)};
		if (cur < ret)
			ret = cur;
	}
	for (int i = 1; i <= 4; i++)
		cout << ret[i] << " ";
}