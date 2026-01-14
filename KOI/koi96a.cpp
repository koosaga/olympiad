#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	vector<int> dp(sz(s) + 1);
	dp[0] = 1;
	for (int i = 0; i + 1 < sz(s); i++) {
		if (dp[i] == 0)
			continue;
		if (s.substr(i, 2) == "01") {
			dp[i + 2] = 1;
		}
		if (s.substr(i, 2) == "10") {
			int j = i + 2;
			if (j == sz(s) || s[j] != '0')
				continue;
			while (j < sz(s) && s[j] == '0')
				j++;
			if (j == sz(s) || s[j] != '1')
				continue;
			while (j < sz(s) && s[j] == '1') {
				dp[++j] = 1;
			}
		}
	}
	cout << (dp.back() ? "SUBMARINE" : "NOISE") << "\n";
}