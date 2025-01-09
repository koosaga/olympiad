#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

string t = "acgw";

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	int c = count(all(s), '1');
	if (c < 3 * n || c > 6 * n) {
		cout << "NIE\n";
		return 0;
	}
	int surp = c - 3 * n;
	for (int i = 0; i < n; i++) {
		int d = min(surp, 3);
		cout << t[d];
		surp -= d;
	}
	cout << "\n";
}