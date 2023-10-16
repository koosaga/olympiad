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
		for (auto &x : a) {
			cin >> x;
			x--;
		}
		int mx = 0;
		vector<int> bad;
		for (int i = 0; i < n - 1; i++) {
			mx = max(mx, a[i]);
			if (mx == i)
				bad.push_back(i);
		}
		cout << sz(bad) << "\n";
		for (int i = 0; i < sz(bad);) {
			int j = i;
			while (j < sz(bad) && bad[j] - bad[i] == j - i)
				j++;
			for (int k = j - 1; k >= i; k--) {
				cout << bad[k] + 1 << " ";
			}
			i = j;
		}
		cout << "\n";
	}
}