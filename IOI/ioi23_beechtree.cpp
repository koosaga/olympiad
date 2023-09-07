#include "beechtree.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

std::vector<int> beechtree(int N, int M, std::vector<int> P, std::vector<int> C) {
	vector<int> sub(N), fucked(N);
	vector<map<int, int>> gph(N);
	for (int i = 1; i < N; i++) {
		if (gph[P[i]].count(C[i]))
			fucked[P[i]] = 1;
		gph[P[i]][C[i]] = i;
	}
	for (int i = N - 1; i >= 0; i--) {
		sub[i]++;
		if (i)
			sub[P[i]] += sub[i];
	}
	auto cmp = [&](int x, int y) {
		if (x == y)
			return false;
		auto it1 = gph[x].begin(), it2 = gph[y].begin();
		while (true) {
			if (it1 == gph[x].end() && it2 == gph[y].end())
				return false;
			if (it1 == gph[x].end())
				return false;
			if (it2 == gph[y].end())
				return true;
			if (it1->first != it2->first)
				return it1->first < it2->first;
			if (sub[it1->second] != sub[it2->second])
				return sub[it1->second] > sub[it2->second];
			it1++;
			it2++;
		}
	};
	vector<int> idx(N);
	iota(all(idx), 0);
	vector<set<int, decltype(cmp)>> ds(N, set<int, decltype(cmp)>(cmp));
	for (int i = N - 1; i >= 0; i--) {
		for (auto &[c, j] : gph[i]) {
			if (fucked[j])
				fucked[i] = 1;
		}
		if (fucked[i])
			continue;
		ds[i].insert(i);
		auto good = [&](int u, int v) {
			for (auto &[c, j] : gph[v]) {
				if (!gph[u].count(c))
					return false;
				if (sub[gph[u][c]] < sub[j])
					return false;
			}
			return true;
		};
		bool ok = 1;
		for (auto &[c, j] : gph[i]) {
			if (sz(ds[idx[i]]) < sz(ds[idx[j]]))
				swap(idx[i], idx[j]);
			for (auto &k : ds[idx[j]]) {
				auto it = ds[idx[i]].insert(k).first;
				if (it != ds[idx[i]].begin() && !good(*prev(it), k))
					ok = 0;
				if (next(it) != ds[idx[i]].end() && !good(k, *next(it)))
					ok = 0;
			}
		}
		if (!ok)
			fucked[i] = 1;
	}
	for (auto &x : fucked)
		x ^= 1;
	return fucked;
}
