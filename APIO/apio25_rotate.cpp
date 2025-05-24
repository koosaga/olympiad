#include "rotate.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

void energy(int N, vector<int> V) {
	vector<int> idx(N);
	iota(all(idx), 0);
	sort(all(idx), [&](int a, int b) { return V[a] < V[b]; });
	for (int i = 0; i < N / 2; i++) {
		rotate({idx[i]}, V[idx[i + N / 2]] - V[idx[i]] + 125000);
	}
}