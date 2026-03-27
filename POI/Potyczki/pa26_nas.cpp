#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 2000005;

int nxt[21][MAXN];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(2 * n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i + n] = a[i];
	}
	vector<int> stk;
	nxt[0][2 * n] = 2 * n;
	for (int i = 2 * n - 1; i >= 0; i--) {
		while (sz(stk) && a[stk.back()] <= a[i])
			stk.pop_back();
		nxt[0][i] = (sz(stk) ? stk.back() : (2 * n));
		stk.push_back(i);
	}
	for (int i = 1; i <= 20; i++) {
		for (int j = 0; j <= 2 * n; j++) {
			nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
		}
	}
	int dap = 0;
	for (int i = 0; i < n; i++) {
		int pos = i, ans = 1;
		for (int j = 20; j >= 0; j--) {
			if (nxt[j][pos] < i + n) {
				ans += (1 << j);
				pos = nxt[j][pos];
			}
		}
		dap = max(dap, ans);
	}
	cout << dap << "\n";
}