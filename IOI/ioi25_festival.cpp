#include "festival.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const lint oo = 1e18;
const int MAXN = 200005;

lint dp[MAXN][205];

vector<int> max_coupons(int A, vector<int> P, vector<int> T) {
	int n = sz(P);
	vector<int> idx, rem;
	for (int i = 0; i < n; i++) {
		if (T[i] > 1)
			idx.push_back(i);
		else
			rem.push_back(i);
	}
	sort(all(rem), [&](int a, int b) { return P[a] < P[b]; });
	sort(all(idx), [&](int a, int b) {
		if (T[a] == 1 && T[b] == 1)
			return P[a] < P[b];
		if (T[a] == 1 || T[b] == 1)
			return T[a] > T[b];
		return 1ll * P[a] * T[a] * (T[b] - 1) < 1ll * P[b] * T[b] * (T[a] - 1);
	});
	int bp = sz(idx);
	lint cur = A;
	for (int i = 0; i < sz(idx); i++) {
		lint nxt = T[idx[i]] * (cur - P[idx[i]]);
		if (cur > nxt) {
			bp = i;
			break;
		}
		cur = min(nxt, oo);
	}
	vector<int> dap(idx.begin(), idx.begin() + bp);
	idx.erase(idx.begin(), idx.begin() + bp);
	for (int i = 0; i <= sz(idx); i++)
		fill(dp[i], dp[i] + 205, -1);
	dp[0][0] = cur;
	for (int i = 0; i < sz(idx); i++) {
		lint p = P[idx[i]], t = T[idx[i]];
		for (int j = 0; j < 200; j++) {
			if (dp[i][j] >= 0)
				dp[i + 1][j] = max(dp[i + 1][j], min(oo, dp[i][j]));
			if (dp[i][j] >= p)
				dp[i + 1][j + 1] = max(dp[i + 1][j + 1], min(oo, (dp[i][j] - p) * t));
		}
	}
	pi gogo{-1, -1};
	for (int i = 0; i < 200; i++) {
		lint cur = dp[sz(idx)][i];
		if (cur < 0)
			continue;
		int cnt = i;
		for (auto &j : rem) {
			if (cur >= P[j]) {
				cur -= P[j];
				cnt++;
			}
		}
		gogo = max(gogo, pi{cnt, i});
	}
	{
		int i = gogo[1];
		lint cur = dp[sz(idx)][i];
		for (auto &j : rem) {
			if (cur >= P[j]) {
				cur -= P[j];
				dap.push_back(j);
			}
		}
		for (int j = sz(idx); j; j--) {
			if (dp[j - 1][i] == min(oo, dp[j][i]))
				continue;
			else {
				i--;
				dap.push_back(idx[j - 1]);
			}
		}
	}
	sort(all(dap), [&](int a, int b) {
		if (T[a] == 1 && T[b] == 1)
			return P[a] < P[b];
		if (T[a] == 1 || T[b] == 1)
			return T[a] > T[b];
		return 1ll * P[a] * T[a] * (T[b] - 1) < 1ll * P[b] * T[b] * (T[a] - 1);
	});
	return dap;
}