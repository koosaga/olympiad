#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

pi operator+(const pi &a, const pi &b) { return pi{a[0] + b[0], a[1] + b[1]}; }
pi operator-(const pi &a, const pi &b) { return pi{a[0] - b[0], a[1] - b[1]}; }
int ccw(pi a, pi b) {
	double apx = 1.0 * a[0] * b[1] - 1.0 * a[1] * b[0];
	if (fabs(apx) > 1e18)
		return apx > 0 ? 1 : -1;
	lint ans = a[0] * b[1] - a[1] * b[0];
	if (ans == 0)
		return 0;
	return ans > 0 ? 1 : -1;
}
int ccw(pi a, pi b, pi c) { return ccw(b - a, c - a); }

struct cht {
	vector<pi> ch;
	bool bad(pi a, pi b, pi c) { return ccw(b - a, b - c) <= 0; }
	void init(vector<pi> &a) {
		for (auto &x : a) {
			if (sz(ch) && ch.back()[0] == x[0])
				continue;
			while (sz(ch) >= 2 && bad(ch[sz(ch) - 2], ch.back(), x))
				ch.pop_back();
			ch.push_back(x);
		}
	}
	lint query(lint x) {
		int s = 0, e = sz(ch) - 1;
		while (s != e) {
			int m = (s + e) / 2;
			if (ch[m][0] * x + ch[m][1] > ch[m + 1][0] * x + ch[m + 1][1])
				e = m;
			else
				s = m + 1;
		}
		return ch[s][0] * x + ch[s][1];
	}
} cht;

vector<lint> a, dap;

void dnc(int l, int r) {
	if (l == r)
		return;
	int m = (l + r) / 2;
	dnc(l, m);
	dnc(m + 1, r);
	vector<pi> L, R;
	for (int j = m + 1; j <= r; j++) {
		pi p{j, a[j]};
		while (sz(R) >= 2 && ccw(R[sz(R) - 2], R.back(), p) >= 0)
			R.pop_back();
		R.push_back(p);
	}
	for (int j = m; j >= l; j--) {
		pi p{-j, -a[j]};
		while (sz(L) >= 2 && ccw(L[sz(L) - 2], L.back(), p) >= 0)
			L.pop_back();
		L.push_back(p);
	}
	pi beg = L[0] + R[0];
	vector<pi> d1, d2;
	for (int k = 0; k + 1 < sz(L); k++) {
		d1.push_back(L[k + 1] - L[k]);
	}
	for (int k = 0; k + 1 < sz(R); k++) {
		d2.push_back(R[k + 1] - R[k]);
	}
	vector<pi> delta(sz(d1) + sz(d2));
	merge(all(d1), all(d2), delta.begin(), [&](const pi &a, const pi &b) { return ccw(a, b) < 0; });
	for (int i = 0; i < sz(delta); i++) {
		dap[beg[0] - 1] = max(dap[beg[0] - 1], beg[1]);
		beg = beg + delta[i];
	}
	dap[beg[0] - 1] = max(dap[beg[0] - 1], beg[1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	cr(a, n + 1);
	cr(dap, n);
	for (int i = 0; i < n; i++) {
		lint z;
		cin >> z;
		a[i + 1] = a[i] + z;
	}
	fill(all(dap), -1e18);
	dnc(0, n);
	vector<pi> points;
	for (int i = 0; i < n; i++) {
		points.push_back({i + 1, dap[i]});
	}
	cht.init(points);
	for (int i = 0; i < q; i++) {
		lint x;
		cin >> x;
		cout << cht.query(x) << "\n";
	}
}