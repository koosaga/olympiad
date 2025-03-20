#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = unsigned long long;
using pi = array<int, 2>;

vector<int> solve(int n, int m, int q, vector<vector<int>> &queries, vector<array<int, 3>> &ask) {
	vector<int> ans(q);
	vector<vector<int>> vect(n);
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			vect[j - 1].push_back(i - 1);
		}
	}
	sort(all(ask), [&](const array<int, 3> &a, const array<int, 3> &b) {
		if (a[0] / 64 != b[0] / 64)
			return a[0] < b[0];
		return a[1] < b[1];
	});
	int p = 0;
	for (int i = 0; i < n; i += 64) {
		int l = i, r = min(i + 64, n);
		vector<lint> chk(n + m);
		for (int j = l; j < r; j++) {
			for (int &k : vect[j]) {
				chk[k] |= (1ull << (j - l));
			}
		}
		for (int i = 0; i < m; i++) {
			if (queries[i][0] == 1) {
				chk[i + n] = chk[queries[i][1]] | chk[queries[i][2]];
			} else if (queries[i][0] == 2) {
				chk[i + n] = chk[queries[i][1]] & chk[queries[i][2]];
			} else {
				chk[i + n] = ~chk[queries[i][1]];
			}
		}
		while (p < sz(ask) && ask[p][0] / 64 == i / 64) {
			ans[ask[p][2]] = (chk[ask[p][1]] >> (ask[p][0] % 64)) % 2;
			p++;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<int>> queries(m);
	for (int i = 0; i < m; i++) {
		int t;
		cin >> t;
		if (t == 1) {
			int x, y;
			cin >> x >> y;
			x--;
			y--;
			queries[i] = {t, x, y};
		}
		if (t == 2) {
			int x, y;
			cin >> x >> y;
			x--;
			y--;
			queries[i] = {t, x, y};
		}
		if (t == 3) {
			int x;
			cin >> x;
			queries[i] = {t, x - 1, 0};
		}
	}
	vector<array<int, 3>> ask;
	for (int i = 0; i < q; i++) {
		int k, v;
		cin >> k >> v;
		ask.push_back({v - 1, k - 1, i});
	}
	auto d = solve(n, m, q, queries, ask);
	for (auto &x : d)
		cout << (x ? "TAK" : "NIE") << "\n";
}
