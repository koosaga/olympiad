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
	vector<int> a(696969);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x]++;
	}
	for (int i = 0; i < sz(a); i++) {
		if (a[i] >= 2)
			a[i + 1] += a[i] / 2;
		a[i] %= 2;
	}
	for (int i = sz(a) - 1; i >= 0; i--) {
		if (a[i]) {
			cout << i << "\n";
			break;
		}
	}
}