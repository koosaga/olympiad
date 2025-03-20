#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

lint f(lint n) {
	lint z = 1;
	while (n && z) {
		z *= (n % 10);
		n /= 10;
	}
	return z;
}

lint rep(lint n) {
	while (n >= 10)
		n = f(n);
	return n;
}
unordered_map<lint, lint> precff[19];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	vector<lint> pwr(19);
	pwr[0] = 1;
	for (int i = 1; i < 19; i++)
		pwr[i] = pwr[i - 1] * 10;
	vector<array<lint, 10>> ans(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
		a[i][1] = i;
		if (a[i][0] == pwr[18]) {
			a[i][0]--;
			ans[i][0]++;
		}
	}
	sort(all(a));
	auto get_rng = [&](lint ll, lint rr) {
		int l = lower_bound(all(a), pi{ll, -1}) - a.begin();
		int r = lower_bound(all(a), pi{rr, -1}) - a.begin();
		return pi{l, r != l};
	};
	precff[0][1] = 1;
	for (int i = 0; i < 18; i++) {
		for (auto &[m, v] : precff[i]) {
			for (int j = 0; j < 10; j++) {
				if ((j * m) % 5 == 0) {
					if ((j * m) % 2 && j * m <= 100000)
						precff[i + 1][j * m] += v;
					else
						precff[i + 1][0] += v;
				} else
					precff[i + 1][m * j] += v;
			}
		}
	}
	unordered_map<lint, lint> dp[1005][2];
	vector<array<lint, 10>> cum(n);
	for (int i = 17; i >= 0; i--) {
		unordered_map<lint, lint> nxt[1005][2];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 2; j++)
				nxt[i][j].reserve(420);
		for (int j = 1; j < 10; j++) {
			auto [l, r] = get_rng(pwr[i] * j, pwr[i] * (j + 1));
			nxt[l][r][j]++;
		}
		vector<vector<pi>> prec(n, vector<pi>(10));
		for (int j = 0; j < n; j++) {
			lint val = a[j][0] / pwr[i + 1];
			for (int k = 0; k < 10; k++) {
				prec[j][k] = get_rng((val * 10 + k) * pwr[i], (val * 10 + k + 1) * pwr[i]);
			}
		}
		for (int l = 0; l < n; l++) {
			for (int r = 0; r < 1; r++) {
				for (auto &[m1, v1] : dp[l][r]) {
					for (auto &[m2, v2] : precff[i + 1]) {
						cum[l][rep(m1 * m2)] += v1 * v2;
					}
				}
			}
			for (int r = 1; r < 2; r++) {
				for (int j = 0; j < 10; j++) {
					int ll, rr;
					ll = prec[l][j][0], rr = prec[l][j][1];
					for (auto &[m, v] : dp[l][r]) {
						if ((j * m) % 5 == 0) {
							if ((j * m) % 2 && j * m <= 100000)
								nxt[ll][rr][j * m] += v;
							else
								nxt[ll][rr][0] += v;
						} else
							nxt[ll][rr][j * m] += v;
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2; j++) {
				swap(dp[i][j], nxt[i][j]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			for (auto &[k, v] : dp[i][j]) {
				cum[i][rep(k)] += v;
			}
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 10; j++)
			cum[i][j] += cum[i - 1][j];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 10; j++) {
			ans[a[i][1]][j] += cum[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 10; j++)
			cout << ans[i][j] << (j == 9 ? " \n" : " ");
	}
}