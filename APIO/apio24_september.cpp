#include "september.h"

#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int solve(int N, int M, std::vector<int> F, std::vector<std::vector<int>> S) {
	vector<int> valids(N);
	vector<vector<int>> gph(N);
	for (int i = 1; i < N; i++)
		gph[F[i]].push_back(i);
	for (auto &v : S) {
		int bads = 0;
		vector<int> balance(N);
		int worse = 0;
		v.push_back(0);
		reverse(all(v));
		vector<int> chk(N);
		for (int j = 0; j < N; j++) {
			chk[v[j]] = 1;
			if (v[j] > 0 && chk[F[v[j]]] == 0)
				bads++;
			for (auto &z : gph[v[j]]) {
				if (chk[z] == 1)
					bads--;
			}
			if (balance[v[j]] != 0)
				worse--;
			balance[v[j]]++;
			if (balance[v[j]] != 0)
				worse++;
			if (balance[S[0][j]] != 0)
				worse--;
			balance[S[0][j]]--;
			if (balance[S[0][j]] != 0)
				worse++;

			if (bads == 0 && worse == 0)
				valids[j]++;
		}
	}
	return count(all(valids), M) - 1;
}
