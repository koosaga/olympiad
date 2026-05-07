#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint a, b, n;
	cin >> a >> b >> n;
	if (n > 50) {
		cout << a * b << "\n";
		return 0;
	}
	vector<lint> fibs(n);
	fibs[1] = 1;
	for (int i = 2; i < n; i++)
		fibs[i] = fibs[i - 1] + fibs[i - 2];
	if (a < fibs[n - 1] || b < fibs[n - 2]) {
		cout << a * b << "\n";
		return 0;
	}
	cout << a * b - (a - fibs[n - 1]) * (b - fibs[n - 2]) << "\n";
}