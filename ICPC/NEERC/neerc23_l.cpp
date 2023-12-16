#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int mod = 998244353;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	for (int i = 1; i < n; i++) {
		int a0 = count(s.begin(), s.begin() + i, 'L');
		int b0 = count(s.begin(), s.begin() + i, 'O');
		int a1 = count(s.begin() + i, s.begin() + n, 'L');
		int b1 = count(s.begin() + i, s.begin() + n, 'O');
		if (a0 != a1 && b0 != b1) {
			cout << i << endl;
			return 0;
		}
	}
	cout << "-1\n";
}