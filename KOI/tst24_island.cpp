#include "island.h"
#include <bits/stdc++.h>

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

void construct_two_trees(int N, vector<int> U, vector<int> V) {
	vector<set<int>> gph(N);
	for (int i = 0; i < N; i++) {
		gph[i].insert((i + 1) % N);
		gph[(i + 1) % N].insert(i);
	}
	for (int i = 0; i < N - 3; i++) {
		gph[U[i]].insert(V[i]);
		gph[V[i]].insert(U[i]);
	}
	queue<int> que;
	for (int i = 0; i < N; i++) {
		if (sz(gph[i]) == 2) {
			que.push(i);
		}
	}
	vector<pi> T1, T2;
	for (int i = 0; i < N - 3; i++) {
		int x = que.front();
		que.pop();
		int y = *gph[x].begin(), z = *gph[x].rbegin();
		gph[x].clear();
		gph[y].erase(x);
		gph[z].erase(x);
		if (sz(gph[y]) == 2)
			que.push(y);
		if (sz(gph[z]) == 2)
			que.push(z);
		T1.push_back({x, y});
		T2.push_back({x, z});
	}
	{
		vector<int> v;
		for (int i = 0; i < N; i++) {
			if (sz(gph[i]) == 2)
				v.push_back(i);
		}
		assert(N == add_vertex(v[0], v[1], v[2]));
		T1.push_back({N, v[0]});
		T1.push_back({N, v[1]});
		T2.push_back({N, v[2]});
		T2.push_back({v[2], v[0]});
		T2.push_back({v[0], v[1]});
		T1.push_back({v[1], v[2]});
	}
	report(T1);
	report(T2);
}