#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> rev(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		rev[x - 1] = i;
	}
	auto cont = [&](int L, int R) { return 1ll * (L + 1) * (n - R); };
	auto monotone = [&](int u, int v, int w) { return (u < v && v < w) || (u > v && v > w); };
	set<pi> s;
	lint ans = 0;
	for (int i = 0; i < n; i++) {
		ans += cont(rev[i], rev[i]);
		auto it = s.lower_bound({rev[i], i});
		vector<pi> L, R;
		while (it != s.end() && sz(R) < 2) {
			R.push_back(*it);
			it++;
		}
		it = s.lower_bound({rev[i], i});
		while (it != s.begin() && sz(L) < 2) {
			L.push_back(*--it);
		}
		s.insert({rev[i], i});
		if (sz(L) >= 2 && sz(R) >= 1 && monotone(L[1][1], L[0][1], R[0][1]))
			ans += cont(L[1][0], R[0][0]);
		if (sz(L) >= 1 && sz(R) >= 2 && monotone(L[0][1], R[0][1], R[1][1]))
			ans += cont(L[0][0], R[1][0]);
		if (sz(R) >= 2 && monotone(i, R[0][1], R[1][1]))
			ans -= cont(rev[i], R[1][0]);
		if (sz(R) >= 1 && sz(L) >= 1 && monotone(L[0][1], i, R[0][1]))
			ans -= cont(L[0][0], R[0][0]);
		if (sz(L) >= 2 && monotone(L[1][1], L[0][1], i))
			ans -= cont(L[1][0], rev[i]);
		cout << ans << "\n";
	}
}