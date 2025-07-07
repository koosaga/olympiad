#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 300005;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	map<string, int> mp;
	for (int i = 0; i < 2; i++) {
		vector<string> vect;
		for (int j = 0;; j++) {
			string s;
			cin >> s;
			if (s[0] == '-' || s[0] == '=')
				break;
			vect.push_back(s);
		}
		assert(sz(vect) % 3 == 0);
		for (int j = 2; j < sz(vect); j += 3) {
			mp[vect[j]] += atoi(vect[j - 2 + i].c_str()) - atoi(vect[j - 1 - i].c_str());
		}
	}
	vector<pair<string, int>> ans;
	for (auto &[s, d] : mp) {
		if (d != 0) {
			ans.push_back({s, d});
		}
	}
	if (sz(ans) == 0) {
		cout << "No differences found.\n";
		return 0;
	}
	for (auto &[s, d] : ans) {
		cout << s << " " << (d > 0 ? "+" : "") << d << "\n";
	}
}