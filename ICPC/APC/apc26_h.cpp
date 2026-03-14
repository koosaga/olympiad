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
	int tc = 1;
	//	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		vector<lint> a;
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			a.push_back(x);
		}
		n = sz(a);
		lint g = 0, sum = 0;
		for (int i = 1; i < n; i++) {
			sum += abs(a[i] - a[i - 1]);
			g = gcd(abs(a[i] - a[i - 1]), g);
		}
		if (g == 0) {
			cout << a[n - 1] << "\n";
			continue;
		}
		g *= 2;
		sum += (a[0] % g == 0 ? g : (a[0] % g));
		cout << sum << "\n";
	}
}