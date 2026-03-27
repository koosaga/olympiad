#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mods[5] = {int(1e9) + 696969, int(1e9) + 7, int(1e9) + 9, 998244353, 993244853};

lint ipow(lint x, lint p, lint m) {
	lint ret = 1, piv = x;
	while (p) {
		if (p & 1)
			ret = ret * piv % m;
		piv = piv * piv % m;
		p >>= 1;
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s[3];
	cin >> s[0] >> s[1] >> s[2];
	int n = sz(s[0]);
	vector<vector<array<lint, 5>>> hashes(3, vector<array<lint, 5>>(n + 1));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < 5; k++) {
				hashes[i][j + 1][k] = hashes[i][j][k] * 10 + (s[i][j] - '0');
				hashes[i][j + 1][k] %= mods[k];
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		lint modinv = ipow(10, mods[i] - 2, mods[i]);
		lint prod = 1;
		for (int k = 0; k <= n; k++) {
			for (int j = 0; j < 3; j++) {
				hashes[j][k][i] *= prod;
				hashes[j][k][i] %= mods[i];
			}
			prod *= modinv;
			prod %= mods[i];
		}
	}
	vector<array<lint, 5>> v;
	for (int i = 0; i <= n; i++) {
		array<lint, 5> a;
		for (int j = 0; j < 5; j++) {
			a[j] = hashes[0][i][j] + hashes[1][i][j] - hashes[2][i][j] + mods[j];
			a[j] %= mods[j];
		}
		v.push_back(a);
	}
	sort(all(v));
	lint ans = 0;
	for (int i = 0; i <= n;) {
		int j = i;
		while (j <= n && v[i] == v[j])
			j++;
		ans += 1ll * (j - i) * (j - i - 1) / 2;
		i = j;
	}
	cout << ans << "\n";
}