#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

void solve() {
	int n, k;
	cin >> n >> k;
	vector<int> cnt(k);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cnt[x - 1]++;
	}
	if (n % 2 == 0) {
		for (auto &x : cnt) {
			if (x % 2) {
				cout << "NO\n";
				return;
			}
		}
		cout << "YES\n";
		vector<int> seq;
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < cnt[i] / 2; j++)
				seq.push_back(i + 1);
		}
		for (int i = 0; i < 2; i++) {
			for (auto &j : seq)
				cout << j << " ";
			reverse(all(seq));
		}
		cout << "\n";
		return;
	}
	int cen = -1;
	for (int i = 0; i < k; i++) {
		if (cnt[i] == 1) {
			if (cen != -1) {
				cout << "NO\n";
				return;
			}
			cen = i + 1;
			cnt[i]--;
		}
	}
	if (cen == -1) {
		for (int i = 0; i < k; i++) {
			if (cnt[i] % 2 == 1) {
				cen = i + 1;
				cnt[i]--;
				break;
			}
		}
	}
	vector<int> odds, evens;
	for (int i = 0; i < k; i++) {
		if (cnt[i] % 2 == 1) {
			odds.push_back(i + 1);
			cnt[i] -= 3;
			assert(cnt[i] >= 0);
		}
		for (int j = 0; j < cnt[i] / 2; j++)
			evens.push_back(i + 1);
	}
	cout << "YES\n";
	for (auto &j : evens)
		cout << j << " ";
	reverse(all(evens));
	vector<int> ans(n - sz(evens) * 2);
	assert(sz(ans) % 6 == 1);
	int m = sz(ans) / 6;
	assert(2 * m == sz(odds));
	ans[3 * m] = cen;
	for (int i = 0; i < m; i++) {
		ans[3 * m + i + 1] = ans[4 * m + i + 1] = ans[2 * m - 2 * i - 2] = odds[i];
		ans[3 * m - i - 1] = ans[2 * i + 1] = ans[6 * m - i] = odds[i + m];
	}
	for (auto &x : ans)
		cout << x << " ";
	for (auto &j : evens)
		cout << j << " ";
	cout << "\n";
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}