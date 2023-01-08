#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 100005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	if (sz(s) % 2 == 0 && count(all(s), 'a') % 2) {
		cout << "-1\n";
		return 0;
	}
	char base = 'a';
	if (count(all(s), base) % 2 != 0)
		base++;
	vector<int> v;
	for (int i = 0; i < sz(s); i++) {
		if (s[i] == base)
			v.push_back(i);
	}
	lint ans = 0;
	for (int i = 0; i < sz(v) / 2; i++) {
		ans += abs(v[i] + v[sz(v) - 1 - i] - sz(s) + 1);
	}
	cout << ans << "\n";
}