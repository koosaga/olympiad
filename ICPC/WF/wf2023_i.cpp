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
	int n, m;
	cin >> n >> m;
	int sum = 0;
	for (int i = 0; i < n * m; i++) {
		int x;
		cin >> x;
		sum += x;
	}
	cout << setprecision(69) << 1.0 * sum / (n * m) << "\n";
}