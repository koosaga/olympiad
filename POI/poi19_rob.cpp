#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

pi solve(lint s, lint e, lint N, lint v) {
	if (v == 0)
		return (s <= 0 && 0 <= e) ? pi{0, N - 1} : pi{0, -1};
	if (v < 0)
		return solve(-e, -s, N, -v);
	s = max(s, 0ll);
	e = min(e, 1ll * v * (N - 1));
	s += v;
	e += v;
	if (s > e)
		return pi{0, -1};
	return pi{(s - 1) / v, e / v - 1};
};
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	lint t;
	cin >> n >> t;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	for (int i = n; i < 4 * n; i++) {
		lint d = a[i - n];
		a.push_back(d);
	}
	n *= 4;
	lint sum = accumulate(all(a), 0ll) + sz(a);
	lint mdlo = (t + 1) % sum;
	lint x, y;
	cin >> x >> y;
	lint vx = 0, vy = 0;
	for (int i = 0; i < n; i++) {
		vx += dx[i % 4] * a[i];
		vy += dy[i % 4] * a[i];
	}
	lint rep = (t + 1) / sum;
	lint px = 0, py = 0;
	auto inPath = [&](lint sx, lint sy, lint ex, lint ey, lint px, lint py) {
		if (sx > ex)
			swap(sx, ex);
		if (sy > ey)
			swap(sy, ey);
		return sx <= px && px <= ex && sy <= py && py <= ey;
	};
	lint ans = 0;
	for (int i = 0; i < n; i++) {
		lint qx = px + dx[i % 4] * a[i];
		lint qy = py + dy[i % 4] * a[i];
		// (px, py) -> (qx, qy)
		lint run = min(mdlo, a[i] + 1);
		if (run > 0) {
			mdlo -= run;
			if (run == a[i] + 1)
				run--;
			lint nx = x - rep * vx, ny = y - rep * vy;
			if (inPath(px, py, px + dx[i % 4] * (run - 1), py + dy[i % 4] * (run - 1), nx, ny))
				ans++;
		}
		lint sx = px, ex = qx - dx[i % 4];
		lint sy = py, ey = qy - dy[i % 4];
		if (sx > ex)
			swap(sx, ex);
		if (sy > ey)
			swap(sy, ey);

		if (rep > 0) {
			auto [s1, e1] = solve(x - ex, x - sx, rep, vx);
			auto [s2, e2] = solve(y - ey, y - sy, rep, vy);
			s1 = max(s1, s2);
			e1 = min(e1, e2);
			if (s1 <= e1)
				ans += e1 - s1 + 1;
		}
		tie(px, py) = make_pair(qx, qy);
	}
	cout << ans << "\n";
}