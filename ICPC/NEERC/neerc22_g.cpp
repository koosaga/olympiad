#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n, m;
	cin >> n >> m;
	vector<int> v[2];
	m--;
	vector<int> cnt(1 << m);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int msk = 0;
		for (int j = 0; j < m; j++) {
			if (s[j + 1] == '1')
				msk |= (1 << j);
		}
		if (s[0] == '0') {
			v[0].push_back(msk);
		} else {
			v[1].push_back(msk);
			cnt[msk]++;
		}
	}
	vector<int> sums[2];
	sums[0].resize(1 << m);
	for (auto &x : v[0])
		sums[0][x]++;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < (1 << m); j++) {
			if ((j >> i) & 1)
				sums[0][j] += sums[0][j - (1 << i)];
		}
	}
	sums[1].resize(1 << m);
	for (auto &x : v[1])
		sums[1][x]++;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < (1 << m); j++) {
			if ((j >> i) & 1)
				sums[1][j - (1 << i)] += sums[1][j];
		}
	}

	vector<double> dp(1 << m);
	dp[0] = 1;
	auto countInsec = [&](int msk) {
		int ans = sz(v[0]) - sums[0][(1 << m) - 1 - msk];
		return ans;
	};
	auto countNoSupset = [&](int msk) {
		int ans = sz(v[1]) - sums[1][msk];
		return ans;
	};
	for (int i = 1; i < (1 << m); i++) {
		if (countInsec(i) == 0) {
			dp[i] = 1;
			continue;
		}
		double sum = 0;
		int coeff = countInsec(i) + countNoSupset(i);
		for (int j = 0; j < (1 << m); j++) {
			sum += dp[i & j] * cnt[j];
		}
		dp[i] = sum / coeff;
	}
	cout << dp[(1 << m) - 1] << "\n";
}