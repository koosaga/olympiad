#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		if (n <= 5) {
			cout << "-1\n";
			continue;
		}
		if (n == 6) {
			cout << "3\n1 3 4\n";
			continue;
		}
		cout << "4\n1 3 " << n - 3 << " " << n - 2 << "\n";
	}
}