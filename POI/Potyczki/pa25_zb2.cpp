#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = unsigned long long;
using pi = array<int, 2>;
const int MAXN = 50005;

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
	int n, m;
	cin >> n >> m;
	vector<int> chk(n);
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		chk[x - 1] = 1;
	}
	vector<bitset<MAXN>> A(n);
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			A[i - 1].set(j - 1);
		}
	}
	int cur = 0;
	while (!chk[cur])
		cur++;
	bitset<MAXN> B = A[cur];
	vector<vector<int>> queries;
	int prv = cur;
	for (int i = cur + 1; i < n; i++) {
		if (B[i] && !chk[i]) {
			queries.push_back({3, i});
			int just = n + sz(queries) - 1;
			queries.push_back({2, just, prv});
			prv = n + sz(queries) - 1;
			B &= ~A[i];
		} else if (!B[i] && chk[i]) {
			B |= A[i];
			queries.push_back({1, i, prv});
			prv = n + sz(queries) - 1;
		}
	}
	if (prv != n + sz(queries) - 1) {
		queries.push_back({3, prv});
		prv = n + sz(queries) - 1;
		queries.push_back({3, prv});
		prv = n + sz(queries) - 1;
	}
	cout << sz(queries) << "\n";
	for (auto &v : queries) {
		for (int j = 0; j < sz(v); j++) {
			if (j)
				v[j]++;
			cout << v[j] << " ";
		}
		cout << "\n";
	}
}