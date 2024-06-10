#include "Bruno.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

namespace {
string s[4] = {"0100201101202102200", "01100201202102200", "1100201202102200", "011002102201200"};
string f = "RGB";
int g(char c) { return find(all(f), c) - f.begin(); }
} // namespace

void init(int N, int l) {}

int bruno(std::string u) {
	if (sz(u) <= 27)
		return 1;
	vector<int> diffs;
	vector<int> mark(9);
	for (int i = 0; i < 27; i++) {
		int d = (g(u[i + 1]) - g(u[i]) + 3) % 3;
		if (d == 0)
			mark[i % 9] = 1;
		diffs.push_back(d);
	}
	int opener = 0;
	for (int i = 0; i < 9; i++) {
		if (!mark[i]) {
			int j = 1;
			while (mark[(i + j) % 9])
				j++;
			if (j % 2 == 1)
				opener = (16 - i) % 9;
		}
	}
	// cout << "begin" << opener << endl;

	vector<int> v;
	int d = 0, m = 1;
	for (int i = 0; i < 4; i++) {
		string foo;
		for (int j = 0; j < 3; j++) {
			foo.push_back('0' + diffs[9 * j + (2 * i + 9 - opener) % 9]);
		}
		//	cout << foo;
		for (int x = 0; x < sz(s[i]); x++) {
			bool ok = 1;
			for (int y = 0; y < sz(foo); y++) {
				if (s[i][(x + y) % sz(s[i])] != foo[y])
					ok = 0;
			}
			if (ok) {
				int z = x;
				if (2 * i < opener)
					z += sz(s[i]) - 1;
				z %= sz(s[i]);
				//	cout << "mod = " << z << endl;
				while (d % sz(s[i]) != z) {
					d += m;
				}
				m *= sz(s[i]);
				break;
			}
		}
	}
	//	cout << d << endl;
	return 9 * d + 1 + opener;
}
