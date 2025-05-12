#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

__int128 binom(__int128 x, int d) {
	__int128 ans = 1;
	for (int i = 0; i < d; i++) {
		ans *= x - i;
		ans /= i + 1;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		vector<int> a(n);
		auto trial = [&](int T) {
			int L = 0;
			for (int i = 0; i < n; i++) {
				int s = 0, e = T - L;
				auto sol = [&](int M) {
					int R = T - L - M;
					__int128 sol = binom(T, 3) - binom(L, 3) - binom(R, 3) - (M + R) * binom(L, 2) - (M + L) * binom(R, 2);
					return sol;
				};
				if (sol(e) < a[i])
					return false;
				while (s != e) {
					int m = (s + e) / 2;
					if (sol(m) < a[i])
						s = m + 1;
					else
						e = m;
				}
				L += s;
			}
			return true;
		};
		for (auto &x : a)
			cin >> x;
		int s = 0, e = 1e8;
		while (s != e) {
			int m = (s + e) / 2;
			if (trial(m))
				e = m;
			else
				s = m + 1;
		}
		cout << s << "\n";
	}
}