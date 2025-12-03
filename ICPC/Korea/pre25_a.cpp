#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> l(n, -1), r(n, n);
	for (int i = 0; i < 2; i++) {
		vector<int> a(n);
		for (auto &x : a)
			cin >> x;
		{
			vector<int> stk;
			for (int i = 0; i < n; i++) {
				while (sz(stk) && a[stk.back()] > a[i]) {
					stk.pop_back();
				}
				if (sz(stk))
					l[i] = max(l[i], stk.back());
				stk.push_back(i);
			}
		}
		{
			vector<int> stk;
			for (int i = n - 1; i >= 0; i--) {
				while (sz(stk) && a[stk.back()] >= a[i]) {
					stk.pop_back();
				}
				if (sz(stk))
					r[i] = min(r[i], stk.back());
				stk.push_back(i);
			}
		}
	}
	vector<int> nxt(n + 1, 0);
	for (int i = 0; i < n; i++) {
		nxt[l[i] + 1] = max(nxt[l[i] + 1], r[i]);
		// l[i] + 1 .. r[i] - 1
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		nxt[i] = max(nxt[i], nxt[i - 1]);
	for (int i = 0; i < n; i = nxt[i])
		cnt++;
	cout << cnt << "\n";
}