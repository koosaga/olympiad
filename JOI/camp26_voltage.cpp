#include "voltage.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

bool solve(int N, int M) {
	int n = N;
	vector<vector<int>> gph(N);
	for (int i = 0; i < N; i++) {
		vector<int> ord;
		for (int j = 0; j < N; j++) {
			if (j != i)
				ord.push_back(j);
		}
		vector<int> founds;
		auto fn = [&](int l, int r) {
			vector<int> X(N), Y(N);
			for (int j = l; j < r; j++)
				X[ord[j]] = Y[ord[j]] = 1;
			for (auto &x : founds)
				X[x] = Y[x] = 1;
			Y[i] = 1;
			return query(X, Y);
		};
		while (fn(0, 0) > 0) {
			int s = 0, e = sz(ord);
			while (s != e) {
				int m = (s + e) / 2;
				if (fn(0, m) > 0)
					s = m + 1;
				else
					e = m;
			}
			assert(s > 0 && s <= sz(ord));
			int j = ord[s - 1];
			gph[i].push_back(j);
			//	gph[j].push_back(i);
			//		cout << i << " " << j << endl;
			founds.push_back(j);
			ord.erase(ord.begin() + s - 1);
		}
		while (fn(0, sz(ord)) < 0) {
			int s = 0, e = sz(ord);
			while (s != e) {
				int m = (s + e) / 2;
				if (fn(0, m) >= 0)
					s = m + 1;
				else
					e = m;
			}
			assert(s > 0 && s <= sz(ord));
			int j = ord[s - 1];
			gph[i].push_back(j);
			//	gph[j].push_back(i);
			//	cout << i << " " << j << endl;

			ord.erase(ord.begin() + s - 1);
		}
	}
	vector<int> seq;
	auto degzero = [&](int v) {
		vector<int> X(n, 1), Y(n, 0);
		for (auto &x : seq)
			X[x] = 0;
		X[v] = 0;
		return query(X, Y) == 0;
	};
	queue<int> que;
	vector<int> in_que(n);
	for (int i = 0; i < n; i++) {
		if (degzero(i)) {
			que.push(i);
			in_que[i] = 1;
		}
	}
	vector<int> ord(n);
	vector<pi> directions;
	while (sz(que)) {
		int x = que.front();
		que.pop();
		seq.push_back(x);
		ord[x] = sz(seq);
		for (auto &y : gph[x]) {
			if (!in_que[y] && degzero(y)) {
				in_que[y] = 1;
				que.push(y);
			}
		}
	}
	if (sz(seq) < n)
		return false;
	for (int i = 0; i < n; i++) {
		for (auto &j : gph[i]) {
			if (ord[i] < ord[j])
				answer(i, j);
		}
	}
	return true;
}
