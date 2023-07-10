#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<int, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	vector<lint> a = {1, 2};
	map<lint, pi> mp;
	mp[1] = pi{1, 2};
	for (int i = 3; i <= 100; i++) {
		if (i % 2 == 1) {
			lint toput = a.back() * 2;
			a.push_back(toput);
		} else {
			lint it = 1;
			while (mp.count(it))
				it++;
			it += a.back();
			a.push_back(it);
		}
		for (int i = 0; i < sz(a) - 1; i++) {
			mp[a.back() - a[i]] = pi{i + 1, sz(a)};
		}
	}
	vector<lint> seqs;
	for (auto &[x, _] : mp)
		seqs.push_back(x);
	int q;
	cin >> q;
	while (q--) {
		lint x;
		cin >> x;
		if (mp.count(x)) {
			cout << mp[x][1] << " " << mp[x][0] << "\n";
		} else {
			int count = lower_bound(all(seqs), x) - seqs.begin();
			cout << 100 + 2 * (x - count) << " " << 99 + 2 * (x - count) << "\n";
		}
	}
}