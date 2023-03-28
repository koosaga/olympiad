#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using line = array<lint, 3>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

vector<int> solve(vector<int> &a, vector<int> &b, int m) {
	vector<int> ret(sz(a), 1e9);
	vector<int> dist(1 << m, 1e9);
	queue<pi> que;
	vector<int> toInsert(1 << m, 1e9);
	for (int i = 0; i < sz(a); i++) {
		int nb = (1 << m) - 1 - b[i];
		toInsert[nb] = min(toInsert[nb], i);
	}
	for (int i = (1 << m) - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			if ((i >> j) & 1)
				toInsert[i ^ (1 << j)] = min(toInsert[i ^ (1 << j)], toInsert[i]);
		}
	}
	vector<vector<int>> ts(sz(a));
	for (int i = 0; i < (1 << m); i++) {
		if (toInsert[i] < sz(a))
			ts[toInsert[i]].push_back(i);
	}
	for (int i = 0; i < sz(a); i++) {
		auto enq = [&](int x, int d) {
			if (dist[x] > d) {
				dist[x] = d;
				que.push({x, d});
			}
		};
		ret[i] = dist[a[i]];
		for (auto &j : ts[i])
			enq(j, 0);
		while (sz(que)) {
			auto [msk, dst] = que.front();
			que.pop();
			if (dist[msk] != dst)
				continue;
			for (int i = 0; i < m; i++) {
				if ((msk >> i) & 1)
					continue;
				enq(msk | (1 << i), dst + 1);
			}
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> pcnt(n);
	vector<int> a(n), b(n);
	int z;
	int ans = 0;
	{
		vector<vector<int>> inp(n, vector<int>(m));
		vector<int> cnt(m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> inp[i][j];
				if (inp[i][j])
					cnt[j]++;
			}
		}
		vector<int> t1, t2;
		for (int i = 0; i < m; i++) {
			if (cnt[i] == n / 2) {
				t1.push_back(i);
			}
			if (cnt[i] == n / 2 + 1) {
				t2.push_back(i);
			}
			if (cnt[i] >= n / 2)
				ans++;
		}
		m = sz(t1) + sz(t2);
		z = sz(t1);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < sz(t1); j++) {
				if (inp[i][t1[j]]) {
					pcnt[i]++;
					b[i] |= (1 << j);
				} else {
					a[i] |= (1 << j);
				}
			}
			for (int j = 0; j < sz(t2); j++) {
				if (inp[i][t2[j]]) {
					a[i] |= (1 << (j + z));
					b[i] |= (1 << (j + z));
				}
			}
		}
	}
	auto d1 = solve(a, b, m);
	reverse(all(a));
	reverse(all(b));
	auto d2 = solve(a, b, m);
	reverse(all(d2));
	for (int i = 0; i < n; i++) {
		int dap = min(d1[i], d2[i]);
		cout << ans - dap - pcnt[i] << "\n";
	}
}
