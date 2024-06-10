#include "Anna.h"
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

std::pair<std::string, int> anna(int N, std::string S) {
	if (N < 28) {
		string dap;
		for (int i = 0; i < N; i++) {
			dap.push_back(f[(g(S[i]) + 1) % 3]);
		}
		return make_pair(dap, N);
	}
	while (sz(S) % 9)
		S.push_back('R');

	string dap;
	for (int i = 0; 9 * i < N; i++) {
		for (int j = 0; j < 4; j++) {
			int d = s[j][i % sz(s[j])] - '0';
			for (int k = 0; k < 3; k++) {
				if (g(S[9 * i + 2 * j]) != k && g(S[9 * i + 2 * j + 1]) != (k + d) % 3) {
					dap.push_back(f[k]);
					dap.push_back(f[(k + d) % 3]);
					break;
				}
			}
		}
		for (int k = 0; k < 3; k++) {
			if (f[k] != S[9 * i + 8] && f[k] != dap.back()) {
				dap.push_back(f[k]);
				break;
			}
		}
	}
	dap.resize(N);
	return make_pair(dap, 28);
}
