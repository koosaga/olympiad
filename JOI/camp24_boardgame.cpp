#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int>> gph(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	vector<int> mark(n);
	string s;
	cin >> s;
	for (int i = 0; i < n; i++) {
		if (s[i] == '0')
			continue;
		for (auto &j : gph[i])
			if (s[j] == '1')
				mark[i] = 1;
	}
	vector<int> src(k);
	for (auto &x : src)
		cin >> x, x--;
	if (count(all(s), '1') == 0) {
		queue<int> que;
		vector<int> dist(n, 1e9);
		dist[src[0]] = 0;
		que.push(src[0]);
		while (sz(que)) {
			int x = que.front();
			que.pop();
			for (auto &y : gph[x]) {
				if (dist[y] > dist[x] + 1) {
					dist[y] = dist[x] + 1;
					que.push(y);
				}
			}
		}
		for (int i = 0; i < n; i++)
			cout << dist[i] << "\n";
		return 0;
	}
	vector<lint> d1(n, 1e16), d2(n, 1e16);
	queue<int> que;
	for (int i = 0; i < n; i++) {
		if (s[i] == '1') {
			d1[i] = 0;
			que.push(i);
		}
	}
	while (sz(que)) {
		int x = que.front();
		que.pop();
		for (auto &y : gph[x]) {
			if (d1[y] > d1[x] + 1) {
				d1[y] = d1[x] + 1;
				que.push(y);
			}
		}
	}
	deque<pi> dq;
	for (int i = 0; i < n; i++) {
		if (mark[i]) {
			d2[i] = 0;
			dq.push_back({0, i});
		}
	}
	while (sz(dq)) {
		auto [d, x] = dq.front();
		dq.pop_front();
		if (d2[x] != d)
			continue;
		for (auto &y : gph[x]) {
			if (s[x] == '0') {
				if (d2[y] > d2[x] + 1) {
					d2[y] = d2[x] + 1;
					dq.push_back({d2[y], y});
				}
			} else {
				if (d2[y] > d2[x]) {
					d2[y] = d2[x];
					dq.push_front({d2[y], y});
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (d1[i] == 0) {
			d1[i] = 2;
			for (auto &j : gph[i])
				if (s[j] == '1')
					d1[i] = 1;
		}
		d2[i]++;
	}
	vector<lint> costs(n + 1);
	vector<lint> v = {1};
	for (int i = 1; i < k; i++) {
		costs[1] += min(d1[src[i]], d2[src[i]]);
		v.push_back(d2[src[i]] - d1[src[i]] + 1);
	}
	for (auto &x : v)
		x = min(x, lint(1e12));
	sort(all(v));
	v.push_back(lint(1e12));
	for (int i = 1; i <= k; i++) {
		for (lint j = v[i - 1] + 1; j <= v[i] && j <= n; j++) {
			costs[j] = costs[j - 1] + (2 * k - i - 1);
		}
	}
	if (k <= 210) {
		vector<lint> ans(n, 1e18);
		ans[src[0]] = 0;
		que.push(src[0]);
		s[src[0]] = '0';
		while (sz(que)) {
			int v = que.front();
			que.pop();
			for (auto &w : gph[v]) {
				if (ans[w] > ans[v] + 1 && s[v] == '0') {
					ans[w] = ans[v] + 1;
					que.push(w);
				}
			}
		}
		vector<lint> dist(n);
		for (int i = 0; i < n; i++) {
			dist[i] = ans[i];
			for (auto &j : gph[i]) {
				dist[i] = min(dist[i], ans[j] + 1 + costs[1]);
			}
		}
		{
			priority_queue<pi, vector<pi>, greater<pi>> pq;
			for (int j = 0; j < n; j++) {
				pq.push({dist[j], j});
			}
			while (sz(pq)) {
				auto [d, v] = pq.top();
				pq.pop();
				if (dist[v] != d || s[v] == '1')
					continue;
				for (auto &w : gph[v]) {
					int cost = 1;
					if (dist[w] > cost + d) {
						dist[w] = cost + d;
						pq.push({dist[w], w});
					}
				}
			}
			for (int j = 0; j < n; j++) {
				ans[j] = min(ans[j], dist[j]);
				dist[j] += max(costs[1] - 2 * k + 2, 0ll);
			}
		}
		for (int i = 1; i <= k; i++) {
			priority_queue<pi, vector<pi>, greater<pi>> pq;
			for (int j = 0; j < n; j++) {
				pq.push({dist[j], j});
			}
			while (sz(pq)) {
				auto [d, v] = pq.top();
				pq.pop();
				if (dist[v] != d)
					continue;
				for (auto &w : gph[v]) {
					int cost = (s[v] == '1' ? (2 * k - i - 1) : 0) + 1;
					if (dist[w] > cost + d) {
						dist[w] = cost + d;
						pq.push({dist[w], w});
					}
				}
			}
			for (int j = 0; j < n; j++) {
				ans[j] = min(ans[j], dist[j]);
				dist[j] += v[i] - 1;
				if (costs[1] > 2 * k - i - 2)
					dist[j]++;
			}
		}
		for (int i = 0; i < n; i++) {
			cout << ans[i] << "\n";
		}
	} else {
		s[src[0]] = '0';
		deque<pi> dq;
		vector<int> minVisit(n, 1e9);
		minVisit[src[0]] = 0;
		dq.push_back({0, src[0]});
		while (sz(dq)) {
			auto [d, x] = dq.front();
			dq.pop_front();
			if (minVisit[x] != d)
				continue;
			for (auto &y : gph[x]) {
				if (s[x] == '1') {
					if (minVisit[y] > minVisit[x] + 1) {
						minVisit[y] = minVisit[x] + 1;
						dq.push_back({minVisit[y], y});
					}
				} else {
					if (minVisit[y] > minVisit[x]) {
						minVisit[y] = minVisit[x];
						dq.push_front({minVisit[y], y});
					}
				}
			}
		}
		vector<vector<lint>> dist(251, vector<lint>(n, 1e18));
		queue<pi> que;
		que.push({0, src[0]});
		dist[0][src[0]] = 0;
		while (sz(que)) {
			auto [t, v] = que.front();
			que.pop();
			int nt = t + (s[v] == '1');
			for (auto &w : gph[v]) {
				if (nt <= minVisit[w] + 250 && dist[nt - minVisit[w]][w] > dist[t - minVisit[v]][v] + 1) {
					dist[nt - minVisit[w]][w] = dist[t - minVisit[v]][v] + 1;
					que.push({nt, w});
				}
			}
		}
		for (int i = 0; i < n; i++) {
			lint ans = 1e18;
			for (int j = 0; j <= 250 && minVisit[i] + j <= n; j++) {
				ans = min(ans, dist[j][i] + costs[minVisit[i] + j]);
			}
			cout << ans << "\n";
		}
	}
}