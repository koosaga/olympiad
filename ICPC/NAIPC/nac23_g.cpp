#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 696969;

struct bit {
	lint tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	lint query(lint x) {
		lint ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
	lint query(lint s, lint e) { return query(e) - query(s - 1); }
} bit;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> a(m + m + n);
	vector<lint> sum(m + m + n + 1);
	for (int i = 0; i < n; i++)
		cin >> a[m + i];
	set<pi> s;
	for (int i = 1; i < sz(sum); i++) {
		if (a[i - 1])
			s.insert({i - 1, a[i - 1]});
		sum[i] = sum[i - 1] + a[i - 1];
	}
	lint ans = 0;
	for (int i = m - 1; i < sz(a); i++) {
		lint q = sum[i + 1] - sum[i - m + 1];
		q = min(q, 1ll * k);
		lint b = 0;
		while ((b = bit.query(i - m + 1, i)) < q) {
			auto it = --s.lower_bound({i + 1, -1});
			auto val = *it;
			s.erase(it);
			lint delta = min(q - b, val[1]);
			bit.add(val[0], delta);
			ans += delta;
			val[1] -= delta;
			if (val[1])
				s.insert(val);
		}
	}
	cout << ans << "\n";
}