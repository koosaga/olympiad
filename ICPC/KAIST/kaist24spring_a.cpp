#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	vector<lint> v;
	lint p = 1;
	for (int i = 0; i < 17; i++) {
		for (int j = 1; j <= 9; j++)
			v.push_back(j * p);
		p = 10 * p + 1;
	}
	while (t--) {
		lint n, k;
		cin >> n >> k;
		vector<lint> ans;
		while (k) {
			lint z = *--upper_bound(all(v), k);
			k -= z;
			ans.push_back(z);
		}
		cout << sz(ans) << "\n";
		for (auto &x : ans)
			cout << x << " ";
		cout << "\n";
	}
}