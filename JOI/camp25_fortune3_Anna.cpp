#include "Anna.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

namespace {
int binom[12][12], R[12][12];
vector<int> Encode(int M, int P, int Q) {
	vector<int> seq(P + Q);
	fill(P + all(seq), 1);
	for (int i = 0; i < M; i++)
		next_permutation(all(seq));
	return seq;
	// generate sequence with 0 P and 1 Q
}
} // namespace

void Anna(int N) {
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
	int C[2] = {}, prv = -1, D = 0;
	for (int i = 0; i < N + C[1] - 10; i++) {
		int k = DrawCard(prv);
		if (k == 0) {
			if (C[0] < 4)
				prv = 0, C[0]++;
			else
				prv = -1;
		} else {
			D++;
			if (D > R[C[1]][10 - C[1]])
				prv = C[0], C[1]++;
			else
				prv = -1;
		}
	}
	if (C[0] < 4) {
		for (int i = 0; i < 10 - C[1] + 1; i++) {
			int k = DrawCard(prv);
			if (k)
				prv = 0;
			else
				prv = -1;
		}
		return;
	}
	if (C[1] == 0) {
		for (int i = 0; i < 10 - C[1] + 1; i++) {
			int k = DrawCard(prv);
			if (k == 0)
				prv = 0;
			else
				prv = -1;
		}
		return;
	}

	int len = 10 - C[1];
	while (R[C[1]][len - 1] >= D) {
		int k = DrawCard(prv);
		if (k) {
			D++;
		}
		len--;
		prv = -1;
	}

	auto seq = Encode(D - R[C[1]][len - 1] - 1, C[1], len);
	int L = 0, R = C[0] + C[1], poot = 0;
	for (int i = 0; i < sz(seq); i++) {
		if (seq[i] == 1) {
			int k = DrawCard(prv);
			if (k == 1)
				prv = L + poot, poot++;
			else
				prv = R + poot;
		} else {
			L++;
			R--;
		}
	}
	DrawCard(prv);
}