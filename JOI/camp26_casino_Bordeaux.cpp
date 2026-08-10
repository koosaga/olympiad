#include "Bordeaux.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

std::string Bordeaux(int N, int L, std::vector<std::vector<int>> T) {
	string S(51, 'A');
	S[49] = (T[0][0] ^ 1) + 'A';
	S[50] = (T[7][7] ^ 1) + 'A';
	vector<pi> points[16];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i + j > 0 && i + j < 14)
				points[i + j].push_back({i, j});
		}
	}
	pi p{0, 0};
	for (int i = 1; i < 14; i++) {
		sort(all(points[i]));
		int sum = 0;
		for (int j = 0; j < sz(points[i]); j += 2) {
			sum ^= T[points[i][j][0]][points[i][j][1]];
		}
		// sum is 1 == even pass
		for (int j = 0; j < sz(points[i]); j++) {
			if (abs(p[0] - points[i][j][0]) + abs(p[1] - points[i][j][1]) != 1)
				continue;
			if (j % 2 != sum) {
				p = points[i][j];
				break;
			}
		}
		T[p[0]][p[1]] ^= 1;
	}
	int C = 0;
	for (int i = 1; i < 14; i++) {
		for (int j = 1; j < sz(points[i]); j++) {
			S[C++] = T[points[i][j][0]][points[i][j][1]] + 'A';
		}
	}
	S.resize(L);
	return S;
}