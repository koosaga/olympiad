#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 500005;
struct bit {
	int tree[MAXT];
	void clear() { memset(tree, 0, sizeof(tree)); }
	void add(int x, int v) {
		for (int i = x + 2; i < MAXT; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;
lint solve(vector<pi> a) {
	vector<int> crd;
	for (auto &[_, y] : a) {
		crd.push_back(y);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for (auto &[_, y] : a) {
		y = lower_bound(all(crd), y) - crd.begin();
	}
	int n = sz(a);
	vector<int> L(n), R(n);
	for (int i = 0; i < n;) {
		int j = i;
		while (j < n && a[i][0] == a[j][0]) {
			L[j] = bit.query(a[j][1] - 1);
			j++;
		}
		for (int k = i; k < j; k++)
			bit.add(a[k][1], +1);
		i = j;
	}
	bit.clear();
	for (int i = n - 1; i >= 0;) {
		int j = i;
		while (j >= 0 && a[i][0] == a[j][0]) {
			R[j] = bit.query(n - a[j][1]);
			j--;
		}
		for (int k = j + 1; k < i + 1; k++)
			bit.add(n + 1 - a[k][1], +1);
		i = j;
	}
	bit.clear();

	lint ret = 0;
	for (int i = 0; i < n; i++)
		ret += 1ll * L[i] * R[i];
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a[i] = {x + y, x - y};
	}
	sort(all(a));
	lint ans = solve(a);
	for (auto &[x, y] : a)
		y = -y;
	ans += solve(a);
	cout << 1ll * n * (n - 1) * (n - 2) / 6 - ans << "\n";
}
