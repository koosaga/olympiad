#include "Bitaro.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

namespace {
vector<lint> dp;
vector<int> normal_to_mask;

void Recurse(int msk, lint ord) {
	if (__builtin_popcount(msk) == 1) {
		//	cout << "leaf " << msk << endl;
		assert(ord == 0);
		normal_to_mask.push_back(msk);
		return;
	} else {
		normal_to_mask.push_back(msk);
		for (int j = msk; j >= msk - j; j = (j - 1) & msk) {
			lint z = dp[j] * dp[msk - j];
			if (ord >= z) {
				ord -= z;
			} else {
				lint A = ord / dp[j];
				lint B = ord % dp[j];
				Recurse(msk - j, A);
				Recurse(j, B);
				// cout << "internal " << msk << endl;

				break;
			}
		}
	}
}

} // namespace

void bitaro(int N, int M, int Q, int K, std::vector<int> A, std::vector<int> B, std::vector<long long> C, std::vector<int> T, std::vector<int> X, std::string s) {
	vector<int> indices(K);
	int ptr = 0;
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < 5; j++) {
			indices[i] *= 2;
			if (s[ptr++] == '1')
				indices[i]++;
		}
	}
	{
		dp.resize(1 << Q);
		for (int i = 1; i < sz(dp); i++) {
			if (__builtin_popcount(i) == 1)
				dp[i] = 1;
			else {
				for (int j = i; j >= (i - j); j = (j - 1) & i)
					dp[i] += dp[j] * dp[i - j];
			}
		}
		lint ord = 0;
		for (int j = 0; j < 60; j++) {
			ord *= 2;
			if (s[ptr++] == '1')
				ord++;
		}
		//	cout << "rec " << ord << endl;

		Recurse((1 << Q) - 1, ord);
	}
	normal_to_mask.push_back(0);
	for (int i = 0; i < Q; i++) {
		for (int j = 0; j < K; j++) {
			int z = normal_to_mask[indices[j]];
			if ((z >> i) & 1) {
				C[X[j]] = 0;
			} else {
				C[X[j]] = 1e18;
			}
		}
		int n = N, m = M;
		vector<vector<array<lint, 3>>> gph(n);
		for (int i = 0; i < m; i++) {
			gph[A[i]].push_back({i, C[i], B[i]});
			gph[B[i]].push_back({i, C[i], A[i]});
		}
		priority_queue<pi, vector<pi>, greater<pi>> pq;
		vector<lint> dist(n, 1e18);
		vector<int> par(n, -1), pae(n, -1);
		dist[0] = 0;
		pq.push({0, 0});
		while (sz(pq)) {
			auto [d, v] = pq.top();
			pq.pop();
			if (dist[v] != d)
				continue;
			for (auto &[i, c, w] : gph[v]) {
				if (dist[w] > dist[v] + c) {
					dist[w] = dist[v] + c;
					par[w] = v;
					pae[w] = i;
					pq.push({dist[w], w});
				}
			}
		}
		vector<int> path;
		for (int z = T[i]; z != 0; z = par[z]) {
			path.push_back(pae[z]);
		}
		reverse(all(path));
		answer(path);
	}
}
