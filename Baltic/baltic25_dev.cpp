#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 60005;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
	}
	vector<pi> states[2];
	for (int i = 0; i < min(6, n); i++) {
		for (int j = -1; j <= 1; j++) {
			states[0].push_back({a[i] + j, 0});
			states[1].push_back({a[i] + j, 0});
		}
	}
	sort(all(states[0]));
	sort(all(states[1]));
	for (int i = 0; i < n; i++) {
		vector<pi> nxt[2];
		for (int j = max(i - 5, 0); j < min(i + 5, n); j++) {
			for (int k = -1; k <= 1; k++) {
				nxt[0].push_back({a[j] + k, lint(1e18)});
				nxt[1].push_back({a[j] + k, lint(1e18)});
			}
		}
		for (int i = 0; i < 2; i++) {
			sort(all(nxt[i]));
			nxt[i].resize(unique(all(nxt[i])) - nxt[i].begin());
			for (auto &[k, v] : nxt[i]) {
				auto it = lower_bound(all(states[i]), pi{k, -1});
				if (it != states[i].end() && (*it)[0] == k)
					v = (*it)[1];
			}
		}
		int k = 0;
		lint cur = 1e18;
		for (auto &[v, r] : nxt[0]) {
			while (k < sz(states[1]) && states[1][k][0] < v) {
				cur = min(cur, states[1][k++][1]);
			}
			r = min(r, cur);
		}
		k = sz(states[0]);
		cur = 1e18;
		reverse(all(nxt[1]));
		for (auto &[v, r] : nxt[1]) {
			while (k > 0 && states[0][k - 1][0] > v) {
				cur = min(cur, states[0][--k][1]);
			}
			r = min(r, cur);
		}
		reverse(all(nxt[1]));
		for (auto &[v, r] : nxt[0]) {
			r += abs(v - a[i]);
		}
		for (auto &[v, r] : nxt[1]) {
			r += abs(v - a[i]);
		}
		states[0] = nxt[0];
		states[1] = nxt[1];
	}
	lint ans = 1e18;
	for (auto &[k, v] : states[0])
		ans = min(ans, v);
	for (auto &[k, v] : states[1])
		ans = min(ans, v);
	cout << ans << "\n";
}