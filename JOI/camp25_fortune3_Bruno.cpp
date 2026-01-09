#include "Bruno.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

namespace {
int binom[12][12], R[12][12];
int decode(vector<int> a, int P, int Q) {
	vector<int> seq(P + Q);
	fill(P + all(seq), 1);
	int it = 0;
	while (true) {
		if (seq == a)
			return it;
		it++;
		next_permutation(all(seq));
	}
}
} // namespace

int Bruno(int N, int _L, std::vector<int> C) {
	for (int i = 0; i < 12; i++) {
		binom[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
		}
	}
	// (R[i, j - 1], R[i, j]] = interval to keep if i partition, j balls
	for (int i = 1; i <= 4; i++) {
		R[i][0] = R[i - 1][(10 - (i - 1))];
		for (int j = 1; j <= 10 - i; j++) {
			R[i][j] = R[i][j - 1] + binom[i + j][i] - 1;
		}
	}
	if (count(all(C), 0) < 4) {
		return N - count(all(C), 0) - (10 - count(all(C), 1));
	}
	if (count(all(C), 1) == 0) {
		return 14 - count(all(C), 0);
	}
	vector<int> pos[2];
	for (int i = 0; i < sz(C); i++)
		pos[C[i]].push_back(i);
	int c0 = 4, c1 = pos[1].end() - lower_bound(all(pos[1]), pos[0][3]);
	c1 = min(c1, 4);
	reverse(all(pos[1]));
	vector<int> counts(c1 + 1);
	for (int i = 0; i < c1; i++) {
		counts[i] += pos[0][i] - (i > 0 ? pos[0][i - 1] : -1) - 1;
		counts[i] += (i > 0 ? pos[1][i - 1] : sz(C)) - pos[1][i] - 1;
	}
	if (c1 == 4) {
		counts[4] += pos[1][3] - pos[0][3] - 1;
	} else {
		counts[c1] += pos[0][c1] - pos[0][c1 - 1] - 1;
		counts[c1] += pos[1][c1 - 1] - pos[0][3] - 1;
	}
	vector<int> a;
	for (int i = 0; i < sz(counts); i++) {
		for (int j = 0; j < counts[i]; j++)
			a.push_back(1);
		if (i + 1 < sz(counts))
			a.push_back(0);
	}
	int P = count(all(a), 0);
	int Q = count(all(a), 1);

	return sz(pos[1]) - c1 + decode(a, P, Q) + 1 + R[P][Q - 1];
}