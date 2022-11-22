#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	lint cnt = 0, ans = 0, used = 0;
	for (auto &x : s) {
		if (x == '(') {
			used = 0;
			cnt++;
		} else if (x == ')') {
			if (!used)
				ans += cnt - 1;
			used = 1;
			cnt--;
		}
	}
	cout << ans << "\n";
}