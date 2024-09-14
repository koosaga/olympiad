#include "hieroglyphs.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;
const int MAXT = 100005;
vector<int> cnt[MAXN][2];

struct bit {
	map<int, int> tree[MAXT];
	bool check(int x, int y, int z) { // <= y, >= z
		for (int i = x + 1; i > 0; i -= i & -i) {
			auto it = tree[i].lower_bound(z);
			if (it != tree[i].end() && it->second >= -y)
				return true;
		}
		return false;
	}
	void insert(int x, int y, int z) {
		for (int i = x + 1; i < MAXT; i += i & -i) {
			auto it = tree[i].lower_bound(z);
			if (it != tree[i].end() && it->second >= -y)
				continue;
			while (it != tree[i].begin()) {
				it--;
				if (it->second <= -y)
					it = tree[i].erase(it);
				else
					break;
			}
			tree[i][z] = -y;
		}
	}
	int query(int x, int z) {
		int ymin = 1e9;
		for (int i = x + 1; i > 0; i -= i & -i) {
			auto it = tree[i].lower_bound(z);
			if (it != tree[i].end())
				ymin = min(ymin, -it->second);
		}
		return ymin;
	}
} T1, T2;

bool verify(vector<int> a, vector<int> b, vector<int> c) {
	vector<vector<pi>> S(sz(c) + 1);
	S[0].push_back({0, 0});
	T1.insert(0, 0, 0);
	T2.insert(0, 0, 0);
	vector<int> counts(MAXN);
	for (auto &x : c)
		counts[x]++;
	vector<int> lastOccur(MAXN);
	for (int i = 0; i < sz(c); i++) {
		int K = counts[c[i]];
		counts[c[i]]--;
		int A = sz(cnt[c[i]][0]), B = sz(cnt[c[i]][1]);
		if (min(A, B) >= K + 1) {
			int m1 = cnt[c[i]][0][A - K - 1], m2 = cnt[c[i]][1][B - K - 1];
			if (T1.check(m1, m2, lastOccur[c[i]]))
				return false;
		}
		int m1 = cnt[c[i]][0][A - K], m2 = cnt[c[i]][1][B - K];
		int ymin = T1.query(m1, lastOccur[c[i]]);
		int xmin = T2.query(m2, lastOccur[c[i]]);
		xmin = 1 + *lower_bound(all(cnt[c[i]][0]), xmin);
		ymin = 1 + *lower_bound(all(cnt[c[i]][1]), ymin);
		S[i + 1].push_back({xmin, m2 + 1});
		S[i + 1].push_back({m1 + 1, ymin});
		sort(all(S[i + 1]));
		if (S[i + 1][0][0] <= S[i + 1][1][0] && S[i + 1][0][1] <= S[i + 1][1][1])
			S[i + 1].pop_back();
		for (auto &[x, y] : S[i + 1]) {
			T1.insert(x, y, i + 1);
			T2.insert(y, x, i + 1);
		}
		lastOccur[c[i]] = i + 1;
	}
	for (int i = 0; i < MAXN; i++) {
		int A = sz(cnt[i][0]), B = sz(cnt[i][1]);
		if (A == 0 || B == 0)
			continue;
		int m1 = cnt[i][0][A - 1], m2 = cnt[i][1][B - 1];
		if (T1.check(m1, m2, lastOccur[i]))
			return false;
	}
	return true;
}

bool subseq(vector<int> s, vector<int> t) {
	int p = 0;
	for (auto &x : s) {
		while (p < sz(t) && t[p] != x)
			p++;
		if (p < sz(t))
			p++;
		else
			return false;
	}
	return true;
}

vector<int> ucs(vector<int> A, vector<int> B) {
	for (int i = 0; i < sz(A); i++)
		cnt[A[i]][0].push_back(i);
	for (int i = 0; i < sz(B); i++)
		cnt[B[i]][1].push_back(i);

	vector<int> chkA(sz(A)), chkB(sz(B));
	for (int i = 0; i < MAXN; i++) {
		if (sz(cnt[i][0]) <= sz(cnt[i][1])) {
			for (auto &x : cnt[i][0])
				chkA[x] = 1;
		} else {
			for (auto &x : cnt[i][1])
				chkB[x] = 1;
		}
	}
	vector<int> ma, mb;
	for (int i = 0; i < sz(A); i++)
		if (chkA[i])
			ma.push_back(i);
	for (int i = 0; i < sz(B); i++)
		if (chkB[i])
			mb.push_back(i);
	int i = 0, j = 0;
	vector<int> ans;
	vector<int> f(sz(ma) + 1);
	vector<int> g(sz(mb) + 1);
	for (int i = 0; i < sz(ma); i++) {
		f[i + 1] = f[i] + 1;
		while (f[i + 1] <= sz(B) && B[f[i + 1] - 1] != A[ma[i]])
			f[i + 1]++;
	}
	g[sz(mb)] = sz(A);
	for (int i = sz(mb) - 1; i >= 0; i--) {
		g[i] = g[i + 1] - 1;
		while (g[i] >= 0 && A[g[i]] != B[mb[i]])
			g[i]--;
	}
	auto test = [&]() { return ma[i] < g[j] && (f[i + 1] <= (j < sz(mb) ? mb[j] : sz(B))); };
	while (i < sz(ma) || j < sz(mb)) {
		if (i < sz(ma) && test())
			ans.push_back(A[ma[i++]]);
		else if (j < sz(mb))
			ans.push_back(B[mb[j++]]);
		else
			return {-1};
	}
	if (!subseq(ans, A) || !subseq(ans, B))
		return {-1};
	if (!verify(A, B, ans))
		return {-1};
	return ans;
}