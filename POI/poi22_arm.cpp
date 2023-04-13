#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

lint powMin(lint x, int p, __int128 n) {
	lint ret = 1;
	for (int i = 0; i < p; i++) {
		ret = min(n, (__int128)ret * x);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, a, b;
	cin >> n >> a >> b;
	n++;
	__int128 ans = 1e36;
	for (int k = 1; k <= 61; k++) {
		// min sum (s_i - 1) * b  (length k)
		// sjt s1 * s2 * .... * sk >= n
		lint st = 2, ed = n;
		while (st != ed) {
			lint m = (st + ed) / 2;
			if (powMin(m, k, n) >= n)
				ed = m;
			else
				st = m + 1;
		}
		int up = 0;
		lint m = st;
		while (up + 1 <= k) {
			if ((__int128)powMin(m, k - up - 1, n) * powMin(m - 1, up + 1, n) >= n)
				up++;
			else
				break;
		}
		ans = min(ans, k * a + (__int128)((m - 2) * up + (m - 1) * (k - up)) * b);
	}
	cout << (lint)ans << "\n";
}