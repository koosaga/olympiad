#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const lint mod = 998244353;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint X, L, R;
	cin >> X >> L >> R;
	// d = X / abc
	auto countIn = [&](lint s, lint e) {
		s = max(s, L);
		e = min(e, R - 1);
		if (s <= e)
			return e - s + 1;
		return 0ll;
	};
	lint ans = 0;
	for (lint a = 1; a * a * a * a <= X; a++) {
		for (lint b = a + 1; a * b * b * b <= X; b++) {
			if (b + 1 >= X / (a * b * (b + 1)))
				continue;
			lint s = b + 1;
			lint e = 2e7;
			while (s != e) {
				lint m = (s + e + 1) / 2;
				if (m < X / (a * b * m))
					s = m;
				else
					e = m - 1;
			}
			ans += countIn(a + b, a + b) * 4 * (s - b);
			ans += countIn(a + b + 1, a + s) * 4;
			ans += countIn(b + b + 1, b + s) * 4;
			lint fuck = X / (a * b);
			{
				lint ts = b + 1, te = s + 1;
				while (ts != te) {
					lint m = (ts + te) / 2;
					if (a + fuck / m < R)
						te = m;
					else
						ts = m + 1;
				}
				lint us = (L - a > 0 ? (fuck / (L - a)) : s);
				us = min(us, s);
				if (ts <= us)
					ans += (us - ts + 1) * 4;
			}
			{
				lint ts = b + 1, te = s + 1;
				while (ts != te) {
					lint m = (ts + te) / 2;
					if (b + fuck / m < R)
						te = m;
					else
						ts = m + 1;
				}
				lint us = (L - b > 0 ? (fuck / (L - b)) : s);
				us = min(us, s);
				if (ts <= us)
					ans += (us - ts + 1) * 4;
			}

			lint sqrtv = (int)sqrt(X / (a * b));
			for (lint c = max(b + 1, sqrtv - 2); c <= min(s, sqrtv + 2); c++) {
				lint d = X / (a * b * c);
				ans += countIn(c + d, c + d) * 4;
			}
			if (b + 1 <= sqrtv - 3) {
				lint ts = b + 1, te = sqrtv - 2;
				while (ts != te) {
					lint m = (ts + te) / 2;
					if (m + fuck / m < R)
						te = m;
					else
						ts = m + 1;
				}
				lint us = b, ue = sqrtv - 3;
				while (us != ue) {
					lint m = (us + ue + 1) / 2;
					if (m + fuck / m >= L)
						us = m;
					else
						ue = m - 1;
				}
				if (ts <= us)
					ans += (us - ts + 1) * 4;
			}
			if (sqrtv + 3 <= s) {
				lint ts = sqrtv + 3, te = s + 1;
				while (ts != te) {
					lint m = (ts + te) / 2;
					if (m + fuck / m >= L)
						te = m;
					else
						ts = m + 1;
				}
				lint us = sqrtv + 2, ue = s;
				while (us != ue) {
					lint m = (us + ue + 1) / 2;
					if (m + fuck / m < R)
						us = m;
					else
						ue = m - 1;
				}
				if (ts <= us)
					ans += (us - ts + 1) * 4;
			}
			ans %= mod;
		}
	}
	cout << ans << "\n";
}