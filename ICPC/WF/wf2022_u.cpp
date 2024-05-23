#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int s, c;
	cin >> s >> c;
	s -= s % 2;
	c -= c % 2;
	if (s == 0) {
		while (c % 4 != 0)
			c -= 2;
		if (c == 8)
			c = 4;
	}
	auto rep = [&](string s, int t) {
		string q;
		for (int i = 0; i < t; i++)
			q += s;
		return q;
	};
	if (c == 8) {
		s -= 2;
		cout << "LL" << rep("S", s / 2);
		cout << "RL" << rep("RLLR", c / 8 - 1) << "LSSL" << rep("RLLR", c / 8 - 1) << "LR";
		cout << rep("S", s / 2) << "\n";
		return 0;
	}
	if (c % 4 != 0)
		s -= 2;
	cout << "LL" << rep("S", s / 2);
	if (c % 8 == 0) {
		cout << "RLRL" << rep("RLLR", c / 8 - 2) << "LRLLRLRL" << rep("RLLR", c / 8 - 2) << "LR";
	}
	if (c % 8 == 2) {
		cout << "RL" << rep("RLLR", c / 8 - 1) << "LRLSLS" << rep("RLLR", c / 8 - 1) << "LR";
	}
	if (c % 8 == 4) {
		cout << rep("RLLR", c / 8) << "LL" << rep("RLLR", c / 8);
	}
	if (c % 8 == 6) {
		cout << "RL" << rep("RLLR", c / 8) << "LSLS" << rep("RLLR", c / 8);
	}
	cout << rep("S", s / 2) << "\n";
}