#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 505000;

pi operator+(const pi &a, const pi &b) { return pi{a[0] + b[0], a[1] + b[1]}; }
struct bit {
	pi tree[MAXT];
	void add(int pos, pi v) {
		for (int i = pos + 2; i < MAXT; i += i & -i)
			tree[i] = tree[i] + v;
	}
	int kth(int k) {
		int pos = 0;
		for (int i = 19; i >= 0; i--) {
			if (pos + (1 << i) < MAXT && tree[pos + (1 << i)][0] < k) {
				pos += (1 << i);
				k -= tree[pos][0];
			}
		}
		return (pos + 1) - 2;
	}
	pi query(int pos) {
		pi ret{0, 0};
		for (int i = pos + 1; i; i -= i & -i)
			ret = ret + tree[i];
		return ret;
	}

} bit;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	int q;
	cin >> q;
	int k = 0;
	vector<vector<array<int, 3>>> queries(n + 1);
	vector<lint> ret;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1)
			k++;
		else {
			int l, r;
			cin >> l >> r;
			queries[min(n, r + k)].push_back({r, +1, sz(ret)});
			queries[min(n, l - 1 + k)].push_back({l - 1, -1, sz(ret)});
			ret.push_back(0);
		}
	}
	auto crd = a;
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for (int i = 0; i < n; i++) {
		int pos = lower_bound(all(crd), a[i]) - crd.begin();
		bit.add(pos, {+1, +a[i]});
		for (auto &[k, b, i] : queries[i + 1]) {
			int qos = bit.kth(k);
			auto [s1, s2] = bit.query(qos);
			ret[i] += b * (s2 + (k - s1) * crd[qos]);
		}
	}
	for (auto &x : ret)
		cout << x << "\n";
}