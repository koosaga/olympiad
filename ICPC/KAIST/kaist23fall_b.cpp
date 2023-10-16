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
	int n;
	cin >> n;
	vector<lint> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	lint op = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] != 0) {
			lint d = -a[i];
			for (int k = i; k <= n; k += i) {
				a[k] += d;
			}
			op += abs(d);
		}
	}
	cout << op << "\n";
}