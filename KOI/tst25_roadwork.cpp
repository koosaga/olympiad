#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int mod = 1e9 + 7;

pi operator+(pi a, pi b) {
	if (a[0] > b[0])
		swap(a, b);
	if (a[0] == b[0]) {
		b[1] += a[1];
		if (b[1] >= mod)
			b[1] -= mod;
	}
	return b;
}

pi roadwork(string S) {
	// validation in model code
	{
		assert(sz(S) > 0 && sz(S) % 2 == 0);
		int N = sz(S) / 2;
		assert(count(all(S), 'A') == N);
		assert(count(all(S), 'B') == N);
	}
	vector<pi> dp(sz(S) + 1);
	dp[0] = {1, 1};
	int acnt = 0, bcnt = 0, j = 0;
	for (int i = 1; i <= sz(S); i++) {
		if (S[i - 1] == 'A')
			acnt++;
		else
			bcnt++;
		while (acnt - (S[j] == 'A') > 0 && bcnt - (S[j] == 'B') > 0) {
			acnt -= (S[j] == 'A');
			bcnt -= (S[j] == 'B');
			j++;
		}
		pi curdp = {1, 1};
		if (acnt > 0 && bcnt > 0)
			curdp = curdp + pi{dp[j][0] + 1, dp[j][1]};
		dp[i] = curdp + dp[i - 1];
	}
	return dp.back();
}