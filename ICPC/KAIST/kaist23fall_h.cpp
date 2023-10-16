#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;

struct bit {
	int tree[MAXN];
	void clear() { memset(tree, 0, sizeof(tree)); }
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
	int kth(int k) {
		k++;
		int pos = 0;
		for (int i = 18; i >= 0; i--) {
			if (pos + (1 << i) < MAXN && tree[pos + (1 << i)] < k) {
				pos += (1 << i);
				k -= tree[pos];
			}
		}
		return pos - 1;
	}
} bit;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n;
	cin >> n;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	a.push_back(lint(5e18));

	vector<pi> goin(n);
	vector<pi> jumps(n + 1);
	vector<lint> sums(n + 1);
	vector<array<lint, 3>> vect;

	lint s = a[0];
	for (int i = 0; i < n; i++) {
		if (a[i + 1] > s + i) {
			// first interval: [s, s + i]
			lint icnt = (a[i + 1] - s) / (i + 1);
			jumps[i + 1] = {s, icnt};
			vect.push_back({s, icnt, i + 1});
			for (int j = i; j >= 0; j--) {
				if (a[j] < s)
					break;
				//	cout << "goin[" << j << "] = " << i + 1 << "," << a[j] - s << endl;
				goin[j] = {i + 1, a[j] - s};
			}
			//		cout << s << " " << i + 1 << " " << icnt << endl;
			s += icnt * (i + 1);
		}
		assert(a[i + 1] <= s + i);
	}
	for (int i = 1; i <= n; i++) {
		sums[i] = sums[i - 1] + jumps[i][1];
	}
	lint q, d;
	cin >> q >> d;
	vector<lint> ans(q);
	vector<array<lint, 4>> queries;
	for (int i = 0; i < q; i++) {
		lint x;
		cin >> x;
		int idx = upper_bound(all(a), x) - a.begin();
		if (idx == 0) {
			ans[i] = x;
			continue;
		}
		auto pos = lower_bound(all(vect), array<lint, 3>{x, lint(9e18), -1}) - vect.begin() - 1;
		lint blockIndex = sums[vect[pos][2] - 1] + (x - vect[pos][0]) / vect[pos][2] + d;
		lint blockPosition = (x - vect[pos][0]) % vect[pos][2];
		// cout << blockIndex << "," << blockPosition << endl;
		if (sums[vect[pos][2]] > blockIndex) {
			ans[i] = x + vect[pos][2] * d;
			continue;
		}
		int term = upper_bound(all(sums), blockIndex) - sums.begin();
		int it = lower_bound(all(goin), pi{vect[pos][2] + 1, -1}) - goin.begin();
		int jt = lower_bound(all(goin), pi{term + 1, -1}) - goin.begin();
		ans[i] = (blockIndex - sums[term - 1]) * term + jumps[term][0];
		queries.push_back({blockPosition, it, jt, i});
	}
	sort(all(queries), [&](const array<lint, 4> &a, const array<lint, 4> &b) { return a[1] > b[1]; });
	for (int i = 0; i < n; i++)
		bit.add(i, 1);
	int p = n;
	for (auto &x : queries) {
		while (p > x[1]) {
			p--;
			goin[p][1] = bit.kth(goin[p][1]);
			bit.add(goin[p][1], -1);
		}
		x[0] = bit.kth(x[0]);
	}
	while (p > 0) {
		p--;
		goin[p][1] = bit.kth(goin[p][1]);
		bit.add(goin[p][1], -1);
	}
	sort(all(queries), [&](const array<lint, 4> &a, const array<lint, 4> &b) { return a[2] < b[2]; });
	for (auto &x : queries) {
		while (p < x[2]) {
			bit.add(goin[p][1], +1);
			p++;
		}
		ans[x[3]] += bit.query(x[0] - 1);
	}
	for (auto z : ans)
		cout << z << "\n";
}