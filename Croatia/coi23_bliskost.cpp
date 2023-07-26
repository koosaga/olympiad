#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 530000;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	string s, t;
	cin >> s >> t;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
			ans += s[i] - 'a';
			ans -= t[i] - 'a';
		} else {
			ans -= s[i] - 'a';
			ans += t[i] - 'a';
		}
	}
	auto sol = [&]() {
		if (ans % 26 == 0)
			cout << "da\n";
		else
			cout << "ne\n";
	};
	sol();
	while (q--) {
		int idx;
		string chr;
		cin >> idx >> chr;
		idx--;
		if (idx % 2 == 0)
			ans -= s[idx] - 'a';
		else
			ans += s[idx] - 'a';
		s[idx] = chr[0];
		if (idx % 2 == 0)
			ans += s[idx] - 'a';
		else
			ans -= s[idx] - 'a';
		sol();
	}
}