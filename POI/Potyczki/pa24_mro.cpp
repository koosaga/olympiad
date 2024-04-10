#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

const int MAXN = 50005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<pi> up(n), dn(n);
	int lcnt = 0, rcnt = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'L') {
			up[i] = pi{0, lcnt};
			lcnt++;
		} else {
			up[i] = pi{1, rcnt};
			rcnt++;
		}
	}
	for (int i = 0; i < n; i++) {
		if (i < lcnt)
			dn[i] = pi{0, i};
		else
			dn[i] = pi{1, i - lcnt};
	}
	for (int i = 0; i < n; i++) {
		if (up[i][0] == dn[i][0])
			cout << 2 * abs(up[i][1] - dn[i][1]) << " ";
		else if (up[i][0] == 1) {
			cout << up[i][1] * 2 + 1 << " ";
		} else {
			cout << (lcnt - up[i][1] - 1) * 2 + 1 << " ";
		}
	}
}