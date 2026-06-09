#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
mt19937 rng(0x14004);
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

void solve() {
	int D = 7560;
	vector<int> v;
	for (int i = 1; i <= D; i++) {
		if ((D * D) % i == 0) {
			int A = D * D / i;
			int B = i;
			if (A % 2 != B % 2)
				continue;
			v.push_back(abs(A - B) / 2);
		}
	}
	assert(sz(v) >= 100);
	int n, k;
	cin >> n >> k;
	int m = 1;
	while (m * (m + 1) / 2 <= k)
		m++;
	int d = k - m * (m - 1) / 2;
	if (d == 0) {
		for (int i = 0; i < m; i++)
			cout << "0 " << i << "\n";
		for (int i = m; i < n; i++)
			cout << randint(-1e9, 1e9) << " " << randint(-1e9, 1e9) << "\n";
	} else {
		for (int i = 0; i < d; i++)
			cout << "0 " << v[i] << "\n";
		for (int i = d; i < m; i++)
			cout << "0 " << 2 * D * D + i << "\n";
		cout << "7560 0" << "\n";
		for (int i = m + 1; i < n; i++)
			cout << randint(-1e9, 1e9) << " " << randint(-1e9, 1e9) << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
}