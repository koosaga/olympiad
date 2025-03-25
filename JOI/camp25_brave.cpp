#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

lint crs(pi a, pi b) { // a[0] < b[0], first int where b is not worse
	return (max(a[1] - b[1], 0ll) + b[0] - a[0] - 1) / (b[0] - a[0]);
}

pi operator+(pi a, pi b) { return pi{a[0] + b[0], a[1] + b[1]}; }
pi operator-(pi a, pi b) { return pi{a[0] - b[0], a[1] - b[1]}; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint n, l, t;
	cin >> n >> l >> t;
	vector<array<lint, 3>> a(n);
	for (auto &[P, H, S] : a) {
		cin >> S >> H >> P;
		S = t - S;
	}
	vector<lint> plist = {0};
	for (auto &[P, H, S] : a)
		plist.push_back(P);
	sort(all(plist));
	plist.resize(unique(all(plist)) - plist.begin());
	vector<pi> hamsu(l + 2);
	sort(all(a), [&](const array<lint, 3> &a, const array<lint, 3> &b) { return a[2] < b[2]; });
	for (int i = 1; i < sz(plist); i++) {
		lint sum = 0;
		vector<pi> seg = {pi{0, 0}};
		for (auto &[P, H, S] : a) {
			if (P < plist[i])
				continue;
			sum += H;
			pi p{sum, -S};
			while (sz(seg) >= 2 && crs(seg[sz(seg) - 2], seg.back()) >= crs(seg.back(), p))
				seg.pop_back();
			seg.push_back(p);
		}
		lint coeff = plist[i] - plist[i - 1];
		for (int i = 0; i < sz(seg); i++) {
			lint L = 0, R = l + 1;
			if (i > 0)
				L = max(L, crs(seg[i - 1], seg[i]));
			if (i + 1 < sz(seg))
				R = min(R, crs(seg[i], seg[i + 1]));
			if (L < R) {
				hamsu[L] = hamsu[L] + pi{seg[i][0] * coeff, seg[i][1] * coeff};
				hamsu[R] = hamsu[R] - pi{seg[i][0] * coeff, seg[i][1] * coeff};
			}
		}
	}
	for (int i = 1; i < sz(hamsu); i++)
		hamsu[i] = hamsu[i - 1] + hamsu[i];
	auto trial = [&](lint l) { return hamsu[l][0] * l + hamsu[l][1]; };
	int q;
	cin >> q;
	while (q--) {
		lint m;
		cin >> m;
		lint s = 0, e = l;
		while (s != e) {
			lint mid = (s + e + 1) / 2;
			if (trial(mid) <= m)
				s = mid;
			else
				e = mid - 1;
		}
		cout << s << "\n";
	}
}