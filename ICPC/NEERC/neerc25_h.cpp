#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

void solve() {
	int n;
	cin >> n;
	vector<lint> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(all(a));
	vector<lint> g(n + 1);
	for (int i = n - 1; i >= 0; i--) {
		g[i] = gcd(g[i + 1], a[i]);
	}
	lint L = 1;
	for (int i = 0; i < n - 1; i++) {
		L = L * (a[i] / gcd(L, a[i]));
		if (L > 2e9) {
			break;
		}
		if (g[i + 1] % L == 0) {
			cout << L << "\n";
			return;
		}
	}
	cout << "-1\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint a, b, c, n;
	cin >> a >> b >> c >> n;
	lint f[3];
	f[0] = gcd(n, a);
	n /= f[0];
	f[1] = gcd(n, b);
	n /= f[1];
	f[2] = gcd(n, c);
	n /= f[2];
	if (n > 1) {
		cout << "-1\n";
	} else {
		cout << f[0] - 1 << " " << f[1] - 1 << " " << f[2] - 1 << "\n";
	}
}