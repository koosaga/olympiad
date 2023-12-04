#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 500005;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

lint hval[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k, m, q;
	cin >> n >> k >> m >> q;
	vector<lint> hsh(k);
	for (int i = 0; i < k; i++) {
		hsh[i] = randint(0, (1ll << 62) - 1);
		set<int> chk;
		for (int j = 0; j < m; j++) {
			int z;
			cin >> z;
			if (chk.count(z))
				continue;
			chk.insert(z);
			hval[z] ^= hsh[i];
		}
	}
	vector<pi> v;
	for (int i = 1; i <= n; i++) {
		v.push_back({hval[i], i});
	}
	sort(all(v));
	while (q--) {
		string s;
		cin >> s;
		lint ans = 0;
		for (int i = 0; i < k; i++) {
			if (s[i] == 'Y')
				ans ^= hsh[i];
		}
		auto it1 = lower_bound(all(v), pi{ans, -1});
		auto it2 = lower_bound(all(v), pi{ans + 1, -1});
		if (it2 - it1 != 1) {
			cout << "0\n";
		} else
			cout << (*it1)[1] << "\n";
	}
}