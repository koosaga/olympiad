#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 1; i < n; i++) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
	int z = 0;
	lint ans = 0;
	while (m--) {
		int d;
		cin >> d;
		ans += abs(a[z + d] - a[z]);
		z += d;
	}
	cout << ans % 100000 << "\n";
	
}