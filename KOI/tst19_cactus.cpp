#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1000005;

int par[20][MAXN];
lint dep[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, q;
	cin >> n >> q;
	vector<lint> g(2 * n), ps(2 * n);
	for (int i = 0; i < n; i++) {
		cin >> g[i];
		g[2 * n - 1 - i] = g[i];
	}
	for (int i = 0; i < n * 2; i++)
		ps[i] = g[i] + (i ? ps[i - 1] : 0);
	vector<int> stk = {-1};
	for (int i = 0; i < n * 2; i++) {
		while (sz(stk) > 1 && g[stk.back()] <= g[i])
			stk.pop_back();
		par[0][i + 1] = stk.back() + 1;
		dep[i + 1] = dep[stk.back() + 1] + (i - stk.back()) * g[i];
		stk.push_back(i);
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n * 2; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	int mx = -1;
	auto sum = [&](int l, int r) {
		int lup = r;
		for (int i = 19; i >= 0; i--) {
			if (par[i][lup] > l)
				lup = par[i][lup];
		}
		mx = g[lup - 1];
		lint moksum = dep[r] - dep[lup] + (lup - l) * g[lup - 1];
		return moksum;
	};
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;
		lint ans = sum(l, r) + sum(2 * n - r, 2 * n - l);
		ans -= 1ll * mx * (r - l);
		ans -= ps[r - 1] - (l ? ps[l - 1] : 0);
		cout << ans << "\n";
	}
}