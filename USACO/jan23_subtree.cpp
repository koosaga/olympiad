#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using line = array<lint, 3>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;

vector<int> gph[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 2; i <= n; i++) {
		int p;
		cin >> p;
		gph[p].push_back(i);
	}
	vector<int> sub(n + 1);
	vector<lint> f(n + 1), On(n + 1);
	for (int i = n; i >= 1; i--) {
		sub[i] += 1;
		for (auto &j : gph[i])
			sub[i] += sub[j];
	}
	for (int i = n; i >= 1; i--) {
		{
			lint ans = 1;
			vector<lint> v = {0, 0};
			for (auto &j : gph[i]) {
				ans += sub[j] + f[j];
				v.push_back((sub[j] + f[j]) - On[j]);
			}
			sort(all(v));
			On[i] = ans - v[sz(v) - 1];
		}
		{
			lint ans = 2;
			vector<lint> v = {0, 0};
			for (auto &k : gph[i]) {
				ans += f[k] + 2 * sub[k];
				v.push_back(f[k] - On[k] + sub[k]);
			}
			sort(all(v));
			ans -= v[sz(v) - 1] + v[sz(v) - 2];
			f[i] = ans;
		}
		lint ans = 2, mpos = 0;
		for (auto &j : gph[i]) {
			ans += f[j] + 2 * sub[j];
			mpos = max(mpos, 2ll * sub[j]);
		}
		f[i] = min(f[i], ans - mpos);
	}
	cout << f[1] << "\n";
}