#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;
const int inf = 1e9;

pi merge(pi a, pi b) { return pi(min(inf, a.first + b.first), max(-inf, min(a.second, a.first + b.second))); }

pi nxt[22][MAXN], F[MAXN];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int m;
	cin >> m;
	string s;
	cin >> s;
	for (int i = 0; i < m; i++) {
		if (s[i] == 'W')
			nxt[0][i] = pi(1, 0);
		else
			nxt[0][i] = pi(-1, -1);
	}
	for (int i = 1; i < 22; i++) {
		for (int j = 0; j < m; j++) {
			int k = (j + n * (1ll << (i - 1))) % m;
			nxt[i][j] = merge(nxt[i - 1][j], nxt[i - 1][k]);
		}
	}
	int g = gcd(n, m);
	for (int j = 0; j < m; j++) {
		F[j] = pi(0, 0);
		int p = j;
		for (int k = 0; k < 22; k++) {
			if (((m / g) >> k) & 1)
				F[j] = merge(F[j], nxt[k][p]), p = (p + n * (1ll << k)) % m;
		}
	}
	lint ret = 2e18;
	for (int i = 0; i < n; i++) {
		pi cur(a[i], a[i]);
		lint ans = i;
		int pos = i % m;
		bool good = 0;
		auto v = F[pos];
		if (cur.first + v.second > 0 && v.first >= 0)
			continue;
		if (cur.first + v.second > 0) {
			lint d = (cur.first + v.second) / -v.first;
			if (d > 0) {
				ans += d * (m / g) * n;
				pos += d * (m / g) * n % m;
				pos %= m;
				cur.first += d * v.first;
				cur.second += (d - 1) * v.first + v.second;
			}
		}
		for (int j = 21; j >= 0; j--) {
			if (merge(cur, nxt[j][pos]).second > 0) {
				cur = merge(cur, nxt[j][pos]);
				ans += n * (1ll << j);
				pos += n * (1ll << j) % m;
				pos %= m;
			} else
				good = 1;
		}
		if (good)
			ret = min(ret, ans);
	}
	if (ret > 1.8e18)
		ret = -1;
	else
		ret++;
	cout << ret << "\n";
}
