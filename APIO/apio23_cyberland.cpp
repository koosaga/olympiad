#include "cyberland.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 100005;

struct disj {
	int pa[MAXN];
	void init(int n) { iota(pa, pa + n + 1, 0); }
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;

double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr) {
	K = min(K, 69);
	vector<vector<pi>> gph(N);
	disj.init(N);
	for (int i = 0; i < M; i++) {
		if (x[i] != H && y[i] != H)
			disj.uni(x[i], y[i]);
		gph[x[i]].push_back({c[i], y[i]});
		gph[y[i]].push_back({c[i], x[i]});
	}
	vector<double> pwr(K + 1, 1);
	for (int i = 1; i <= K; i++)
		pwr[i] = pwr[i - 1] / 2;
	arr[0] = 0;
	vector<vector<double>> dist(K + 1, vector<double>(N, 1e18));
	using node = tuple<double, int, int>;
	priority_queue<node, vector<node>, greater<node>> pq;
	auto enq = [&](int k, int x, double d) {
		if (dist[k][x] > d) {
			dist[k][x] = d;
			pq.push({d, k, x});
		}
	};
	enq(K, H, 0);
	while (sz(pq)) {
		auto [d, k, v] = pq.top();
		pq.pop();
		if (dist[k][v] < d)
			continue;
		if (arr[v] == 0)
			return d;
		for (auto &[c, w] : gph[v]) {
			if (disj.find(w) != disj.find(0))
				continue;

			enq(k, w, d + c * pwr[K - k]);
			if (arr[v] == 2 && k > 0) {
				enq(k - 1, w, d + c * pwr[K - k + 1]);
			}
		}
	}
	return -1;
}