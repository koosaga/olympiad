
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<int, 2>;

string solve(string s) {
	if (count(all(s), '1') == sz(s))
		return s;
	int p = 0;
	while (p < sz(s) && s[p] == '1')
		p++;
	int q = p;
	while (q < sz(s) && s[q] == '0')
		q++;
	int d = p - min(q - p, p);
	string ans = s;
	for (int i = 0; i < sz(s) - p; i++) {
		if (s[i + d] == '1')
			ans[i + p] ^= 1;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		string s;
		int n;
		cin >> n >> s;
		if (count(all(s), '1') == n) {
			s.back() = '0';
			cout << s << "\n";
			continue;
		}
		int p = 0;
		while (p < n && s[p] == '0')
			p++;
		s = s.substr(p);
		if (sz(s) == 0)
			cout << "0\n";
		else
			cout << solve(s) << "\n";
	}
}