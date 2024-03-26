#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 300005;

int par[20][MAXN];
lint dep[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, d;
	cin >> n >> d;
	vector<lint> a(n), sum(n + 1), dum(n), g(n);
	for (auto &x : a)
		cin >> x;
	for (int i = 0; i + 1 < n; i++) {
		dum[i + 1] = dum[i] + (a[i + 1] % d < a[i] % d);
	}
	for (int i = 0; i < n; i++) {
		sum[i + 1] = sum[i] + a[i] / d - dum[i];
		g[i] = a[i] / d - dum[i];
	}
	vector<int> stk = {-1};
	for (int i = 0; i < n; i++) {
		while (sz(stk) > 1 && g[stk.back()] >= g[i])
			stk.pop_back();
		par[0][i + 1] = stk.back() + 1;
		dep[i + 1] = dep[stk.back() + 1] + (i - stk.back()) * g[i];
		stk.push_back(i);
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;
		int lup = r;
		for (int i = 19; i >= 0; i--) {
			if (par[i][lup] > l)
				lup = par[i][lup];
		}
		lint moksum = dep[r] - dep[lup] + (lup - l) * g[lup - 1];
		lint opt = g[lup - 1];
		if (opt + dum[l] < 0)
			cout << "-1\n";
		else
			cout << sum[r] - sum[l] - moksum << "\n";
	}
}