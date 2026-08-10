#include "Azzurro.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<int>> Azzurro(int N, int L, string S) {
	while (sz(S) < 51)
		S.push_back('A');
	vector<vector<int>> x(N, vector<int>(N, 0));
	x[0][0] = S[49] - 'A';
	x[7][7] = S[50] - 'A';
	vector<pi> points[16];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i + j > 0 && i + j < 14)
				points[i + j].push_back({i, j});
		}
	}
	int C = 0;
	for (int i = 1; i < 14; i++) {
		sort(all(points[i]));
		for (int j = 1; j < sz(points[i]); j++) {
			x[points[i][j][0]][points[i][j][1]] = S[C++] - 'A';
		}
		for (int j = 2; j < sz(points[i]); j += 2) {
			x[points[i][0][0]][points[i][0][1]] ^= x[points[i][j][0]][points[i][j][1]];
		}
	}
	return x;
}