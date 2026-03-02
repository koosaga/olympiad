#include "sauce.h"
#include <bits/stdc++.h>
using namespace std;

int solve(int N) {
	int ans = 0;
	for (int i = 1; i < 64; i++) {
		vector<int> sum;
		int grp = 0;
		for (int j = 0; j < 6; j++) {
			if ((i >> j) & 1) {
				for (int k = j; k < N; k += 6)
					sum.push_back(k);
				grp++;
			}
		}
		if (grp <= 0 || grp > 3)
			continue;

		ans += query(sum) * (grp == 3 ? 1 : (grp == 2 ? -3 : 6));
	}
	return ans;
}
