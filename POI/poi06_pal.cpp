#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

string p(string s) {
	vector<int> fail(sz(s) + 1);
	int p = 0;
	for (int i = 1; i < sz(s); i++) {
		while (p && s[i] != s[p])
			p = fail[p];
		if (s[i] == s[p])
			p++;
		fail[i + 1] = p;
	}
	int g = sz(s) - fail[sz(s)];
	return sz(s) % g ? s : s.substr(0, g);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<string> q;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		string s;
		cin >> s;
		q.push_back(p(s));
	}
	sort(all(q));
	lint ans = 0;
	for (int i = 0; i < n;) {
		int j = i;
		while (j < n && q[i] == q[j])
			j++;
		ans += 1ll * (j - i) * (j - i);
		i = j;
	}
	cout << ans << "\n";
}