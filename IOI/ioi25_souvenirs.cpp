#include "souvenirs.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

void buy_souvenirs(int n, long long P0) {
	vector<vector<int>> rref(n);
	vector<lint> sums(n);
	vector<lint> ans(n, -1);
	vector<int> calls(n);
	ans[0] = P0;
	cr(rref[0], n);
	rref[0][0] = 1;
	sums[0] = ans[0];
	auto fuck = [&](int i, int j) {
		while (i < j) {
			int k = accumulate(all(rref[i]), 0);
			//	cerr << "fuck " << i << " " << k << endl;
			if (k == 1) {
				auto [in, rem] = transaction(sums[i] - 1);
				sums[i + 1] = sums[i] - 1 - rem;
				assert(sz(rref[i + 1]) == 0);
				cr(rref[i + 1], n);
				for (auto &x : in) {
					calls[x]++;
					if (ans[x] != -1) {
						sums[i + 1] -= ans[x];
					} else {
						rref[i + 1][x] = 1;
					}
				}
				i++;
			} else {
				lint prv = sums[i];
				auto [nin, nrem] = transaction(prv / k);
				i = nin[0];
				sums[i] = prv / k - nrem;
				assert(sz(rref[i]) == 0);
				cr(rref[i], n);
				for (auto &x : nin) {
					calls[x]++;
					if (ans[x] != -1) {
						sums[i] -= ans[x];
					} else {
						rref[i][x] = 1;
					}
				}
			}
		}
	};
	for (int i = n - 1; i >= 0; i--) {
		if (!sz(rref[i])) {
			int k = i;
			while (sz(rref[k]) == 0)
				k--;
			for (int j = k + 1; j < n; j++) {
				if (rref[k][j] == 1 && ans[j] != -1) {
					rref[k][j] = 0;
					sums[k] -= ans[j];
				}
			}
			fuck(k, i);
		}
		assert(sz(rref[i]));
		ans[i] = sums[i];
		for (int j = i + 1; j < n; j++) {
			if (rref[i][j])
				ans[i] -= ans[j];
		}
	}
	for (int i = 1; i < n; i++)
		for (int j = calls[i]; j < i; j++)
			transaction(ans[i]);
}