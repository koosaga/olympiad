#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

struct pi {
	lint first, second;
	int cnt;
	bool operator<(const pi &p) const {
		if (first == p.first)
			return second < p.second;
		return first < p.first;
	}
	bool operator>(const pi &p) const {
		if (first == p.first)
			return second > p.second;
		return first > p.first;
	}
};

typedef priority_queue<pi, vector<pi>, greater<pi>> pque;

int n;
lint c[300005];
vector<int> gph[300005];

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
	pi t = pi{max(-c[x], 0ll), max(c[x], 0ll), 1};
	while (!pq.empty() && (t.second <= t.first || t.second >= pq.top().first)) {
		auto x = pq.top();
		lint tmp = t.second - t.first + x.second - x.first;
		t.first = max(t.first, t.first - t.second + x.first);
		t.second = tmp + t.first;
		t.cnt += x.cnt;
		pq.pop();
	}
	if (t.first < t.second)
		pq.push(t);
	return pq;
}

int main() {
	int x;
	lint curhel;
	scanf("%d %lld", &n, &curhel);
	lint zz = curhel;
	for (int i = 1; i <= n; i++) {
		int p;
		scanf("%lld %d", &c[i], &p);
		gph[p].push_back(i);
		gph[i].push_back(p);
	}
	auto ret = dfs(0, -1);
	int ans = 0;
	while (!ret.empty()) {
		auto t = ret.top();
		ret.pop();
		if (curhel < t.first)
			break;
		curhel += t.second - t.first;
	}
	printf("%lld\n", curhel - zz);
}
