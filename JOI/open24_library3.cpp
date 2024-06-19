#include "library3.h"
#include <bits/stdc++.h>

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

void solve(int n) {
	vector<int> ans(n);
	iota(all(ans), 0);
	int q = query(ans);
	for (int i = 0; i < n; i++) {
		if (q == 0)
			break;
		vector<int> E;
		for (int j = 0; j < n; j++) {
			if (i != j)
				E.push_back(j);
		}
		while (sz(E) > 1) {
			vector<int> nxt = ans;
			vector<int> rot = {i};
			for (int j = 0; j < sz(E) / 2; j++)
				rot.push_back(E[j]);
			for (int j = 0; j < sz(rot) - 1; j++)
				swap(nxt[rot[j]], nxt[rot[j + 1]]);
			if (query(nxt) == q + sz(rot) - 1) {
				E.erase(E.begin(), E.begin() + sz(E) / 2);
			} else {
				E.resize(sz(E) / 2);
			}
		}
		swap(ans[i], ans[E[0]]);
		if (query(ans) == q - 1) {
			q--;
		} else {
			swap(ans[i], ans[E[0]]);
		}
	}
	answer(ans);
}