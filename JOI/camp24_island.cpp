#include "island.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

void solve(int n, int L) {
	vector<int> v;
	vector<int> ord(n + 1), chk(n + 1);
	for (int i = 1; i <= n - 1; i++) {
		v.push_back(query(1, i));
		ord[v.back()] = i;
	}
	for (auto &x : v) {
		if (chk[x])
			continue;
		for (int j = 1; j <= n - 1; j++) {
			int z = query(x, j);
			answer(z, x);
			chk[z] = 1;
			if (ord[z] < ord[x])
				break;
		}
	}
}