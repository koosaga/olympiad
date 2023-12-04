#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int MAXN = 100005;
struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 3; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 3; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

int h[16][MAXN / 2];
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> x(n / 2);
	for (int i = 0; i < n / 2; i++) {
		cin >> x[i] >> h[0][i];
	}
	for (int i = 1; i < 16; i++) {
		for (int j = (1 << (i - 1)); j < n / 2; j++) {
			h[i][j] = min(h[i - 1][j], h[i - 1][j - (1 << (i - 1))]);
		}
	}
	vector<array<int, 3>> vect;
	while (q--) {
		int px, py;
		cin >> px >> py;
		int is = lower_bound(all(x), px) - x.begin();
		int ie = is;
		int poz = 2 * (is - 1);
		if (x[is] == px)
			poz++;
		if (py == 0) {
			vect.push_back({0, poz, n / 2 - 1});
			continue;
		}
		for (int i = 15; i >= 0; i--) {
			if (ie + (1 << i) <= n / 2 && h[i][ie + (1 << i) - 1] >= py)
				ie += (1 << i);
			if (is >= (1 << i) && h[i][is - 1] >= py)
				is -= (1 << i);
		}
		vect.push_back({is, poz, ie});
	}
	sort(all(vect), [&](const array<int, 3> &a, const array<int, 3> &b) { return a[2] - a[0] < b[2] - b[0]; });
	int cnt = 0;
	for (auto &x : vect) {
		if (bit.query(x[1]) == 0) {
			cnt++;
			bit.add(2 * x[0] - 1, +1);
			bit.add(2 * x[2], -1);
		}
	}
	cout << cnt << "\n";
}