#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	lint m;
	cin >> n >> m;
	lint psum = 0;
	for (int i = 0; i < n; i++) {
		lint x;
		cin >> x;
		if (psum + (__int128)(i + 1) * (x - 1) >= m) {
			cout << i << "\n";
			return 0;
		}
		psum += x;
	}
	cout << n << "\n";
}