#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> a(n + 1);
	for (int i = 0; i < n; i++)
		cin >> a[i + 1];
	lint dap = 1;
	for (int i = 1; i <= n; i++) {
		if (a[i - 1] < a[i]) {
			dap += a[i] - a[i - 1] + 1;
		}
	}
	cout << dap << "\n";
}