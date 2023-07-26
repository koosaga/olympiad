#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using llf = long double;
const int MAXN = 15005;

int ps[MAXN], chk[MAXN], n, S;
bitset<MAXN> dp[MAXN];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
		a[i][1] = i + 1;
		S += a[i][0];
	}
	sort(all(a));
	reverse(all(a));
	for (int i = 0; i < n; i++) {
		ps[a[i][0]]++;
	}
	for (int i = MAXN - 2; i > 0; i--)
		ps[i] += ps[i + 1];
	for (int i = 1; i < MAXN; i++)
		ps[i] += ps[i - 1];
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		chk[x] = 1;
	}
	dp[0][0] = 1;
	for (int j = S; j > 0; j--) {
		if (chk[j]) {
			bitset<MAXN> filter = 1;
			for (int i = 0; i * j <= S && i <= S; i++) {
				for (int k = ps[i] + 1; k <= ps[i + 1]; k++)
					filter[k] = 1;
				dp[i + 1] |= ((dp[i] << j) & filter);
			}
		}
	}
	for (int i = 1; i <= S; i++) {
		if (dp[i][S]) {
			vector<int> b;
			int j = 1;
			for (int k = i; k; k--) {
				while (true) {
					if (S >= j && dp[k - 1][S - j] && chk[j]) {
						b.push_back(j);
						S -= j;
						break;
					} else
						j++;
				}
			}
			// (j, i, S)
			cout << sz(b) << "\n";
			sort(all(b));
			vector<vector<int>> indices(MAXN + 1);
			for (int i = 0; i < sz(a); i++) {
				indices[a[i][0]].push_back(a[i][1]);
			}
			int thr =MAXN;
			for (auto &x : b) {
				cout << x;
				vector<pi> toput;
				while (!sz(indices[thr]))
					thr--;
				int lastthr = thr;
				for (int j = 0; j < x; j++) {
					while (!sz(indices[thr]))
						thr--;
					int x = indices[thr].back();
					indices[thr].pop_back();
					cout << " " << x;
					if (thr > 1)
						toput.push_back({x, thr - 1});
				}
				for (auto &[x, p] : toput)
					indices[p].push_back(x);
				thr = lastthr;
				cout << "\n";
			}
			return 0;
		}
	}

	cout << "-1\n";
}