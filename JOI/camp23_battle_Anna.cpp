#include "Anna.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

namespace {
// cheating good
int f[72] = {94, 231, 134, 9, 26, 169, 106, 174, 164, 22, 92, 89, 45, 243, 176, 62, 154, 253, 8, 145, 208, 91, 33, 52, 79, 244, 86, 121, 151, 201, 43, 188, 187, 161, 34, 77, 15, 195, 35, 85, 235, 224, 40, 51, 206, 119, 11, 149, 100, 181, 138, 17, 152, 241, 148, 122, 237, 126, 0, 68, 215, 189, 242, 239, 116, 254, 194, 66, 120, 216, 214, 238};
} // namespace

void Anna(int X, int Y, int N, std::string S) {
	int input = X + ((Y - X + 8) % 8) * 8;
	if (X == Y && sz(S) == 43 && S[42] == 'B')
		input += 64;
	for (int i = 0; i < 8; i++) {
		if (i != X && i != Y)
			Paint(i, i, (f[input] >> i) & 1);
	}
	int cnt = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == X || j == Y || i == j)
				continue;
			if (cnt < sz(S))
				Paint(i, j, S[cnt++] - 'A');
			else
				Paint(i, j, 0);
		}
	}
}
