#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int align(vector<int> a, vector<int> b) {
	if (sz(a) < sz(b))
		swap(a, b);
	vector<int> dp(sz(b) + 1, 1e9);
	dp[0] = 0;
	for (int i = 0; i < sz(a); i++) {
		vector<int> nxt(sz(b) + 1, 1e9);
		vector<int> cost(sz(b) + 1);
		for (int j = 1; j <= sz(b); j++) {
			for (int k = i - 1; k <= i + 1; k++) {
				if (k >= 0 && k < sz(a))
					cost[j] = max(cost[j], -a[k] - b[j - 1]);
			}
		}
		for (int j = 1; j <= sz(b); j++) {
			nxt[j] = min(max(dp[j], cost[j]), max(dp[j - 1], cost[j]));
		}
		dp = nxt;
	}
	int up = max(dp[sz(b)], 0);
	int delta = a.back() + b.back() + up;
	assert(delta >= 0);
	return up + delta + sz(a) - sz(b);
}

pair<vector<int>, vector<int>> make_array(string U, string D) {
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
	return make_pair(seqU, seqD);
}

#include <algorithm>
#include <assert.h>
#include <bitset>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <tuple>
#include <vector>
#define xx first
#define yy second

using namespace std;

template <typename T, typename Pr = less<T>> using pq = priority_queue<T, vector<T>, Pr>;
using i64 = long long int;
using ii = pair<int, int>;
using ii64 = pair<i64, i64>;

void solve1(string s) {
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
	auto [u, d] = make_array(U, D);
	printf("%d\n", align(u, d) + sz(s));
}

pair<int, int> check(string s) {
	int maxx = 0, maxy = 0;
	int dx = 0, dy = -1;
	int x = 0, y = 0;

	for (auto &c : s) {
		int ndx, ndy;
		if (c == 'L') {
			ndx = -dy;
			ndy = dx;
		} else {
			ndx = dy;
			ndy = -dx;
		}

		dx = ndx;
		dy = ndy;

		x += dx;
		y += dy;
	}

	return ii{x, y};
}

void solve2(string s) {
	int st = 0;

	int fst = s.find("LL");

	rotate(s.begin(), s.begin() + fst, s.end());

	vector<int> corner;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'L' && s[(i + 1) % s.size()] == 'L')
			corner.push_back(i);
	}

	// corner에서 시작해서 x,y 움직임 추적
	auto [w1, h1] = check(s.substr(corner[0], corner[1] - corner[0]));
	auto [h2, w2] = check(s.substr(corner[1], corner[2] - corner[1]));
	auto [w3, h3] = check(s.substr(corner[2], corner[3] - corner[2]));
	auto [h4, w4] = check(s.substr(corner[3]) + s.substr(0, corner[0])); /*
	 cout << w1 << " " << h1 << endl;
	 cout << w2 << " " << h2 << endl;
	 cout << w3 << " " << h3 << endl;
	 cout << w4 << " " << h4 << endl;*/
	int ans = (max(w1 + w4, w2 + w3) + max(h1 + h2, h3 + h4));
	if (w1 + w4 == w2 + w3 && h1 + h2 == h3 + h4 && (w1 + h1 == 1 || w2 + h2 == 1 || w3 + h3 == 1 || w4 + h4 == 1)) {
		ans++;
	}
	printf("%d\n", 2 * ans);
}

int main() {
	string s;
	cin >> s;

	if (sz(s) > 10000)
		solve2(s);
	else
		solve1(s);
}