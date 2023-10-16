#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (auto &x : a)
			cin >> x;
		pi ans{int(-2e9), -1};
		for (int i = 0; i < 20; i++) {
			int av = (1 << i) - 1;
			vector<int> chk(n + 5);
			for (int j = 0; j < n; j++) {
				int z = (a[j] & av);
				chk[min(z, n)] = 1;
			}
			int p = 0;
			while (chk[p])
				p++;
			ans = max(ans, pi{p, av});
		}
		cout << ans[1] << "\n";
	}
}