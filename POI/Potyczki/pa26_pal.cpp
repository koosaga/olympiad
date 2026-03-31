#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

string solve(int n, int k) {
	if (k == 1) {
		string s = "PA";
		if (n <= sz(s))
			return s.substr(0, n);
		return "";
	}
	if (k == 2) {
		string s = "PPAA";
		if (n <= sz(s))
			return s.substr(0, n);
		return "";
	}
	if (k == 3) {
		string s = "PPPAPAAA";
		if (n <= sz(s))
			return s.substr(0, n);
		return "";
	}
	string s;
	while (sz(s) < n) {
		s += "AAPPAPAAPPAP";
	}
	for (int i = 0; i < k; i++)
		s += "A";
	return s.substr(sz(s) - n, n);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		string z = solve(n, k);
		if (sz(z) == 0)
			cout << "NIE\n";
		else
			cout << z << "\n";
	}
}