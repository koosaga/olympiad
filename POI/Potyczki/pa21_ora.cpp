#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 1005;
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> occ(n + 1, 1e9);
	for (int i = 0; i < n; i++) {
		int z;
		cin >> z;
		occ[z] = min(occ[z], i);
	}
	sort(all(occ));
	lint ans = 0;
	for (int i = 0; i < m; i++) {
		if (occ[i] > 1e8) {
			cout << "-1\n";
			return 0;
		}
		ans += occ[i] - i;
	}
	cout << ans << "\n";
}