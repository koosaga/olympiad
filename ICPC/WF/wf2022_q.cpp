#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1000005;

struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[i + 1] = x - 1;
	}
	a[0] = n;
	lint ans = 2 * n;
	for (int i = n; i >= 1; i--) {
		int l = a[i - 1], r = a[i];
		if (l > r)
			swap(l, r);
		ans += (bit.query(r) - bit.query(l));
		ans += (bit.query(n) - bit.query(r));
		bit.add(a[i], +1);
	}
	cout << setprecision(69) << ans * 0.5 << "\n";
}