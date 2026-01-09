#include "polygon.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

lint align(vector<int> a, vector<int> b, int h) {
	vector<vector<int>> dp(sz(a), vector<int>(sz(b), 1e9));
	dp[0][0] = 1;
	for (int i = 0; i < sz(a); i++) {
		for (int j = 0; j < sz(b); j++) {
			if (a[i] >= h - b[j])
				dp[i][j] = 1e9;
			if (i + 1 < sz(a))
				dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
			if (j + 1 < sz(b))
				dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
			if (i + 1 < sz(a) && j + 1 < sz(b) && max(a[i], a[i + 1]) + max(b[j], b[j + 1]) < h)
				dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 1);
		}
	}
	return dp[sz(a) - 1][sz(b) - 1];
}

vector<int> norm(vector<int> a) {
	vector<int> b(sz(a));
	for (int i = 0; i + 1 < sz(a);) {
		int j = i + 1;
		while (j < sz(a) && a[j] > a[j - 1])
			j++;
		for (int k = i; k < j; k++)
			b[k] = max(b[k], k - i);
		i = j;
	}
	for (int i = 0; i + 1 < sz(a);) {
		int j = i + 1;
		while (j < sz(a) && a[j] < a[j - 1])
			j++;
		for (int k = i; k < j; k++)
			b[k] = max(b[k], j - 1 - k);
		i = j;
	}
	return b;
}
int polygon(string s) {
	int dx = 1, dy = 0;

	vector<int> type1, type2;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'L' && s[(i + 1) % s.size()] == 'L') {
			if (dy == 0)
				type1.push_back(i);
			else
				type2.push_back(i);
		}

		int ndx, ndy;
		if (s[i] == 'L') {
			ndx = -dy;
			ndy = dx;
		} else {
			ndx = dy;
			ndy = -dx;
		}

		dx = ndx;
		dy = ndy;
	}

	vector<int> corner = type1.size() == 2 ? type1 : type2;
	sort(all(corner));
	rotate(s.begin(), s.begin() + corner[0] + 1, s.end());
	string U = s.substr(0, corner[1] - corner[0]);
	string D = s.substr(corner[1] - corner[0]);

	assert(U[0] == U.back() && U.back() == 'L');
	assert(D[0] == D.back() && D.back() == 'L');
	vector<int> seqU, seqD;
	{
		int curH = 0;
		for (int i = 0; i + 2 < sz(U); i += 2) {
			seqU.push_back(curH);
			if (U[i + 1] == 'L')
				curH--;
			else
				curH++;
		}
		seqU.push_back(curH);
	}
	{
		int curH = 0;
		for (int i = 0; i + 2 < sz(D); i += 2) {
			seqD.push_back(curH);
			if (D[i + 1] == 'L')
				curH--;
			else
				curH++;
		}
		seqD.push_back(curH);
		reverse(all(seqD));
		for (int i = 0; i < sz(seqD); i++)
			seqD[i] -= curH;
	}
	for (auto &x : seqD)
		x = -x;
	for (auto &x : seqU)
		x = -x;

	seqU = norm(seqU);
	seqD = norm(seqD);

	lint ans = 1e18;
	for (int i = 1;; i++) {
		ans = min(ans, align(seqD, seqU, i) * i);
		if (ans <= (i + 1) * max(sz(seqD), sz(seqU)))
			break;
	}
	return ans;
}