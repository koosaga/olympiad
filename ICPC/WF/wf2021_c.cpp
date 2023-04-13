#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

lint powExceed(lint q, lint n, lint m) {
	if (q <= 1)
		n = min(n, 2ll);
	lint z = 1;
	for (int i = 0; i < n; i++) {
		z *= q;
		if (z > m)
			return 1;
	}
	return z > m;
}

lint powInt(lint q, lint n) {
	if (q <= 1)
		n = min(n, 2ll);
	lint z = 1;
	for (int i = 0; i < n; i++) {
		z *= q;
	}
	return z;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, m;
	cin >> n >> m;
	for (int q = 1;; q++) {
		if (powExceed(q, n - 1, m))
			break;
		for (int p = 1; p < q; p++) {
			__int128 sum = 0;
			if (powExceed(q - p, n - 1, m))
				continue;
			for (int i = 0; i < n; i++) {
				sum += (__int128)powInt(q, i) * powInt(q - p, n - 1 - i);
				if (sum > m)
					break;
			}
			if (m % sum == 0) {
				cout << p << " " << q << endl;
				return 0;
			}
		}
	}
	cout << "impossible\n";
}