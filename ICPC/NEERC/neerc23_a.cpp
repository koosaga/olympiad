#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
typedef priority_queue<pi, vector<pi>, greater<pi>> pque;

int n;
lint c[200005];
vector<int> gph[200005];

pque dfs(int x, int p) {
	pque pq;
	for (auto &i : gph[x]) {
		if (i == p)
			continue;
		auto t = dfs(i, x);
		if (t.size() > pq.size())
			swap(t, pq);
		while (!t.empty()) {
			pq.push(t.top());
			t.pop();
		}
	}
	pi t = pi(max(-c[x], 0ll), max(c[x], 0ll));
	while (!pq.empty() && (t.second <= t.first || t.second >= pq.top().first)) {
		auto x = pq.top();
		lint tmp = t.second - t.first + x.second - x.first;
		t.first = max(t.first, t.first - t.second + x.first);
		t.second = tmp + t.first;
		pq.pop();
	}
	if (t.first < t.second)
		pq.push(t);
	return pq;
}

int main() {
	scanf("%lld", &c[1]);
	int m;
	scanf("%d", &m);
	n = 1;
	for (int i = 1; i <= m; i++) {
		int p = 1;
		int sz;
		scanf("%d", &sz);
		while (sz--) {
			scanf("%lld", &c[++n]);
			gph[p].push_back(n);
			gph[n].push_back(p);
			p = n;
		}
	}
	auto ret = dfs(1, 0);
	lint curhel = 0;
	while (!ret.empty()) {
		auto t = ret.top();
		ret.pop();
		if (curhel < t.first)
			break;
		curhel += t.second - t.first;
	}
	cout << curhel << "\n";
}
