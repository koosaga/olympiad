#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	int q;
	cin >> q;
	vector<array<int, 3>> B(q);
	for (int i = 0; i < q; i++) {
		for (int j = 0; j < 3; j++)
			cin >> B[i][j];
	}
	vector<int> ans(q, 1e9);
	for (int i = 0; i < 3; i++) {
		int triv = 0;
		vector<int> a[3][3], p[3][3];
		int S[3][3];
		for (int i = 0; i < n - 1;) {
			int j = i + 1;
			while (s[j] == '?')
				j++;
			if (s[i] != s[j])
				triv++;
			if (j - i > 1) {
				int L = s[i] - 'A', R = s[j] - 'A';
				if (L > R)
					swap(L, R);
				a[L][R].push_back(j - i - 1);
			}
			i = j;
		}
		for (int i = 0; i < 3; i++) {
			for (int j = i; j < 3; j++) {
				sort(all(a[i][j]));
				p[i][j].push_back(0);
				int sum = 0;
				for (auto &x : a[i][j]) {
					sum += x;
					p[i][j].push_back(sum);
				}
				S[i][j] = S[j][i] = sum;
			}
		}
		vector<int> zz[2], zzs[2];
		for (int i = 0; i < 2; i++) {
			for (int j = i; j + 2 <= sz(a[0][1]); j += 2) {
				zz[i].push_back(a[0][1][j] + a[0][1][j + 1]);
			}
			zzs[i].push_back(0);
			int sum = 0;
			for (auto &j : zz[i]) {
				sum += j;
				zzs[i].push_back(sum);
			}
		}
		vector<array<int, 4>> Q1;
		for (int i = 0; i < q; i++) {
			bool ok = 1;
			for (int j = 0; j < 3; j++) {
				if (!(S[j][j] <= B[i][j] && B[i][j] <= accumulate(S[j], S[j] + 3, 0))) {
					ok = 0;
					break;
				}
			}
			if (ok) {
				ans[i] = min(ans[i], triv);
				continue;
			}

			if (B[i][2] > accumulate(S[2], S[2] + 3, 0) && B[i][0] <= S[0][0] + S[0][1] &&
				B[i][1] <= S[1][1] + S[0][1]) {
				int xl = upper_bound(all(p[0][0]), B[i][0]) - p[0][0].begin() - 1;
				int yl = upper_bound(all(p[1][1]), B[i][1]) - p[1][1].begin() - 1;
				for (int r = 0; r < 2 && r <= sz(a[0][1]); r++) {
					int thres = B[i][0] + B[i][1] - (r ? a[0][1][0] : 0);
					if (thres < 0)
						continue;
					int s = 0, e = n;
					auto query = [&](int m) {
						int i1 = upper_bound(all(a[0][0]), m) - a[0][0].begin();
						int i2 = upper_bound(all(a[1][1]), m) - a[1][1].begin();
						int i3 = upper_bound(all(zz[r]), m) - zz[r].begin();
						i1 = min(i1, xl);
						i2 = min(i2, yl);
						return pi{i1 + i2 + i3, p[0][0][i1] + p[1][1][i2] + zzs[r][i3]};
					};
					while (s != e) {
						int m = (s + e + 1) / 2;
						auto p = query(m);
						if (p[1] <= thres)
							s = m;
						else
							e = m - 1;
					}
					auto p = query(s);
					auto q = query(s + 1);
					p[0] += min((thres - p[1]) / (s + 1), q[0] - p[0]);
					ans[i] = min(ans[i], triv + 2 * sz(a[0][0]) + 2 * sz(a[1][1]) + sz(a[0][1]) - r - 2 * (int)p[0]);
				}
			}
			if (B[i][2] < S[2][2] && B[i][1] >= S[1][1] && B[i][0] >= S[0][0]) {
				// one small case
				int afuck = B[i][0] - S[0][0], b = B[i][1] - S[1][1];
				int k = upper_bound(all(p[2][2]), B[i][2]) - p[2][2].begin() - 1;
				int sum = p[2][2][k];
				int c = B[i][2] - sum;
				tie(afuck, b, c) = make_tuple(max({0, afuck - S[0][1] - S[0][2], S[2][2] - sum - b - c}),
											  max({0, b - S[1][2] - S[1][0], S[2][2] - sum - afuck - c}),
											  max({0, c - S[2][0] - S[2][1], S[2][2] - sum - afuck - b}));
				int l = afuck, r = S[2][2] - sum - b;
				if (r - l >= c) {
					Q1.push_back({sz(a[2][2]) - k, l, r, i});
				}
			}
		}
		sort(all(Q1));
		reverse(all(a[2][2]));
		vector<int> dp(n + 1);
		dp[0] = 1;
		{
			set<int> s = {0};
			int p = 0;
			while (p < sz(Q1) && Q1[p][0] == 0) {
				ans[Q1[p][3]] = min(ans[Q1[p][3]], triv + (Q1[p][1] > 0));
				p++;
			}
			for (int i = 0; i < sz(a[2][2]);) {
				int j = i;
				while (j < sz(a[2][2]) && a[2][2][i] == a[2][2][j])
					j++;
				int B = a[2][2][i], M = j - i;
				vector<pi> upd;
				for (int j = 0; j < B; j++) {
					int last_dp = -1e9;
					for (int k = j; k <= n; k += B) {
						if (dp[k])
							last_dp = k / B;
						else {
							int val = k / B - last_dp;
							if (val <= M) {
								upd.push_back({val, k});
							}
						}
					}
				}
				sort(all(upd));
				int pp = 0;
				while (p < sz(Q1) && Q1[p][0] <= j) {
					while (pp < sz(upd) && upd[pp][0] + i <= Q1[p][0]) {
						s.insert(upd[pp][1]);
						dp[upd[pp][1]] = 1;
						pp++;
					}
					auto it = s.lower_bound(Q1[p][1]);
					ans[Q1[p][3]] =
						min(ans[Q1[p][3]], triv + 2 * Q1[p][0] + ((it != s.end() && *it <= Q1[p][2]) ? 0 : 1));
					p++;
				}
				while (pp < sz(upd)) {
					s.insert(upd[pp][1]);
					dp[upd[pp][1]] = 1;
					pp++;
				}
				i = j;
			}
		}
		for (auto &j : s) {
			if (j != '?')
				j = (j - 'A' + 1) % 3 + 'A';
		}
		for (auto &j : B)
			rotate(j.begin(), j.begin() + 2, j.end());
	}
	for (auto &x : ans)
		cout << x << "\n";
}