#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 4000005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, v, c;
	cin >> n >> v >> c;
	vector<pi> a(n);
	lint sum = 0;
	for (auto &[d, x] : a) {
		cin >> x >> d;
		sum += x;
	}
	sort(all(a), [&](const pi &a, const pi &b) { return a[0] * v + a[1] * c < b[0] * v + b[1] * c; });
	bitset<MAXN> bs, filter;
	bs[0] = 1;
	int ts = 0;
	for (auto &[d, x] : a) {
		while (ts < MAXN && ts * c < d * v) {
			filter[ts++] = 1;
		}
		while (ts > 0 && (ts - 1) * c >= d * v) {
			filter[--ts] = 0;
		}
		bs |= ((bs & filter) << x);
	}
	for (int i = MAXN - 1; i >= 0; i--) {
		if (bs[i]) {
			sum += 1ll * i * (c - 1);
			break;
		}
	}
	cout << sum << "\n";
}