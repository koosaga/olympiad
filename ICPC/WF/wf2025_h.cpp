#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

lint table[9][20];
lint dp[20][1005][2][2][20];

int counts(lint d, vector<int> &chk) {
	int ans = 0;
	while (d > 0) {
		if (chk[d % 10])
			ans++;
		d /= 10;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint n;
	string s;
	cin >> s >> n;
	lint fuck = 0;
	for (auto &x : s)
		fuck = fuck * 10 + x - '0';
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	int M = a[0];
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	vector<lint> dist(M, 1e18);
	auto enq = [&](lint v, lint d) {
		if (dist[v] > d) {
			dist[v] = d;
			pq.push({d, v});
		}
	};
	enq(0, 0);
	while (sz(pq)) {
		auto [d, v] = pq.top();
		pq.pop();
		if (dist[v] != d)
			continue;
		for (int j = 0; j < n; j++) {
			enq((v + a[j]) % M, d + a[j]);
		}
	}
	for (int i = 0; i <= 8; i++) {
		vector<int> chk(10);
		chk[i] = 1;
		if (i == 6)
			chk[9] = 1;
		memset(dp, 0, sizeof(dp));
		dp[0][0][1][0][0] = 1;
		for (int j = 0; j < sz(s); j++) {
			for (int mv = 0; mv < M; mv++) {
				for (int lo = 0; lo < 2; lo++) {
					for (int lz = 0; lz < 2; lz++) {
						for (int dig = 0; dig < 10; dig++) {
							if (lo == 1 && dig > s[j] - '0')
								continue;
							int nmv = (mv * 10 + dig) % M;
							int nlo = (lo & (dig == s[j] - '0'));
							for (int cnt = 0; cnt < 19; cnt++) {
								dp[j + 1][nmv][nlo][lz | (dig > 0)][cnt + (lz > 0 || i > 0) * chk[dig]] += dp[j][mv][lo][lz][cnt];
							}
						}
					}
				}
			}
		}
		for (int t = 0; t < M; t++) {
			if (dist[t] > 1e9)
				continue;
			for (int j = 0; j < 2; j++) {
				for (int jj = 0; jj < 2; jj++) {
					for (int k = 0; k < 20; k++) {
						table[i][k] += dp[sz(s)][t][j][jj][k];
					}
				}
			}
			for (int j = t; j < dist[t] && j <= fuck; j += M) {
				table[i][counts(j, chk)]--;
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		vector<int> chk(10);
		chk[i] = 1;
		if (i == 6)
			chk[9] = 1;

		int ans = counts(fuck, chk);
		for (int j = 0; j < 20; j++) {
			if (table[i][j])
				ans = max(ans, j);
		}
		if (i == 0)
			ans = max(ans, 1);
		if (ans > 0)
			cout << i << " " << ans << "\n";
	}
}