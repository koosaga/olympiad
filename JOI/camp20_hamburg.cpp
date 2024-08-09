// n^2, probably optimizable, but i wont, sry

#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int inf = 1e9;

struct rect {
	int sx, sy, ex, ey;
};

vector<pi> trace;

vector<rect> chop(vector<rect> a, pi p) {
	vector<rect> z;
	for (auto &r : a) {
		if (r.sx <= p[0] && p[0] <= r.ex && r.sy <= p[1] && p[1] <= r.ey)
			continue;
		z.push_back(r);
	}
	return z;
}

void backtrack(vector<rect> a, int k, int p) {
	if (sz(a) == 0) {
		for (int i = 0; i < p; i++) {
			cout << trace[i % sz(trace)][0] << " " << trace[i % sz(trace)][1] << "\n";
		}
		exit(0);
	}
	if (k == 0)
		return;
	int xmin = 2e9, ymin = 2e9, xmax = -2e9, ymax = -2e9;
	for (auto &x : a) {
		xmin = min(xmin, x.ex);
		ymin = min(ymin, x.ey);
		xmax = max(xmax, x.sx);
		ymax = max(ymax, x.sy);
	}
	vector<pi> cp = {pi{xmax, ymax}, pi{xmax, ymin}, pi{xmin, ymax}, pi{xmin, ymin}};
	for (auto &v : cp) {
		trace.push_back(v);
		backtrack(chop(a, v), k - 1, p);
		trace.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<rect> a(n);
	for (auto &x : a) {
		cin >> x.sx >> x.sy >> x.ex >> x.ey;
	}
	backtrack(a, k, k);
	vector<int> vx, vy;
	for (auto &x : a) {
		vx.push_back(x.sx);
		vy.push_back(x.sy);
	}
	sort(all(vx));
	sort(all(vy));
	vx.resize(unique(all(vx)) - vx.begin());
	vy.resize(unique(all(vy)) - vy.begin());
	int xmin = inf, xmax = -inf, ymin = inf, ymax = -inf;
	for (auto &x : a) {
		x.sx = lower_bound(all(vx), x.sx) - vx.begin();
		x.sy = lower_bound(all(vy), x.sy) - vy.begin();
		x.ex = upper_bound(all(vx), x.ex) - vx.begin() - 1;
		x.ey = upper_bound(all(vy), x.ey) - vy.begin() - 1;
		xmin = min(xmin, x.ex);
		ymin = min(ymin, x.ey);
		xmax = max(xmax, x.sx);
		ymax = max(ymax, x.sy);
	}
	vector<pi> I(4);
	I[0] = I[2] = {ymin + 1, ymax - 1};
	I[1] = I[3] = {xmin + 1, xmax - 1};
	vector<pi> transeuropeexpress[2];
	auto cap = [&](pi p, pi q) { return pi{max(p[0], q[0]), min(p[1], q[1])}; };
	auto contain = [&](rect &r, int sx, int ex, int sy, int ey) { return r.sx <= sx && ex <= r.ex && r.sy <= sy && ey <= r.ey; };
	vector<int> L[4], R[4];
	for (int i = 0; i < 4; i++) {
		L[i].resize(i % 2 == 0 ? sz(vy) : sz(vx));
		R[i].resize(i % 2 == 0 ? sz(vy) : sz(vx));
	}
	fill(all(L[0]), xmax - 1);
	fill(all(L[1]), ymin + 1);
	fill(all(L[2]), xmin + 1);
	fill(all(L[3]), ymax - 1);
	fill(all(R[0]), xmax - 1);
	fill(all(R[1]), ymin + 1);
	fill(all(R[2]), xmin + 1);
	fill(all(R[3]), ymax - 1);
	for (auto &x : a) {
		if (contain(x, xmin, xmin, ymin, ymax))
			continue;
		if (contain(x, xmax, xmax, ymin, ymax))
			continue;
		if (contain(x, xmin, xmax, ymin, ymin))
			continue;
		if (contain(x, xmin, xmax, ymax, ymax))
			continue;
		if (x.sx <= xmin && x.ex < xmax)
			if (ymin < x.sy && x.ey < ymax)
				I[0] = cap(I[0], pi{x.sy, x.ey});
		if (x.sy > ymin && ymax >= x.ey)
			if (xmin < x.sx && x.ex < xmax)
				I[1] = cap(I[1], pi{x.sx, x.ex});
		if (x.sx > xmin && xmax >= x.ex)
			if (ymin < x.sy && x.ey < ymax)
				I[2] = cap(I[2], pi{x.sy, x.ey});
		if (x.sy <= ymin && x.ey < ymax)
			if (xmin < x.sx && x.ex < xmax)
				I[3] = cap(I[3], pi{x.sx, x.ex});
		if (x.sx <= xmin && xmax <= x.ex) {
			transeuropeexpress[0].push_back({x.sy, x.ey});
		} else if (x.sy <= ymin && ymax <= x.ey) {
			transeuropeexpress[1].push_back({x.sx, x.ex});
		} else {
			if (contain(x, xmin, xmin, ymax, ymax)) {
				R[0][x.sy - 1] = min(R[0][x.sy - 1], x.ex);
				L[1][x.ex + 1] = max(L[1][x.ex + 1], x.sy);
			}
			if (contain(x, xmax, xmax, ymax, ymax)) {
				R[1][x.sx - 1] = max(R[1][x.sx - 1], x.sy);
				L[2][x.sy - 1] = max(L[2][x.sy - 1], x.sx);
			}
			if (contain(x, xmax, xmax, ymin, ymin)) {
				R[2][x.ey + 1] = max(R[2][x.ey + 1], x.sx);
				L[3][x.sx - 1] = min(L[3][x.sx - 1], x.ey);
			}
			if (contain(x, xmin, xmin, ymin, ymin)) {
				R[3][x.ex + 1] = min(R[3][x.ex + 1], x.ey);
				L[0][x.ey + 1] = min(L[0][x.ey + 1], x.ex);
			}
		}
	}
	for (int i = 1; i < sz(L[0]); i++)
		L[0][i] = min(L[0][i], L[0][i - 1]);
	for (int i = 1; i < sz(L[1]); i++)
		L[1][i] = max(L[1][i], L[1][i - 1]);
	for (int i = sz(L[2]) - 2; i >= 0; i--)
		L[2][i] = max(L[2][i], L[2][i + 1]);
	for (int i = sz(L[3]) - 2; i >= 0; i--)
		L[3][i] = min(L[3][i], L[3][i + 1]);

	for (int i = sz(R[0]) - 2; i >= 0; i--)
		R[0][i] = min(R[0][i], R[0][i + 1]);
	for (int i = sz(R[1]) - 2; i >= 0; i--)
		R[1][i] = max(R[1][i], R[1][i + 1]);
	for (int i = 1; i < sz(R[2]); i++)
		R[2][i] = max(R[2][i], R[2][i - 1]);
	for (int i = 1; i < sz(R[3]); i++)
		R[3][i] = min(R[3][i], R[3][i - 1]);

	vector<pi> fn[2];
	fn[0].resize(sz(vy));
	fn[1].resize(sz(vx));
	for (int i = I[0][0]; i <= I[0][1]; i++) {
		fn[0][i] = I[2];
		for (auto &[l, r] : transeuropeexpress[0]) {
			if (l <= i && i <= r)
				continue;
			fn[0][i][0] = max(fn[0][i][0], l);
			fn[0][i][1] = min(fn[0][i][1], r);
		}
	}
	for (int i = I[1][0]; i <= I[1][1]; i++) {
		fn[1][i] = I[3];
		for (auto &[l, r] : transeuropeexpress[1]) {
			if (l <= i && i <= r)
				continue;
			fn[1][i][0] = max(fn[1][i][0], l);
			fn[1][i][1] = min(fn[1][i][1], r);
		}
	}
	for (int x = I[0][0]; x <= I[0][1]; x++) {
		for (int y = I[1][0]; y <= I[1][1]; y++) {
			if (fn[0][x][0] > fn[0][x][1] || fn[1][y][0] > fn[1][y][1])
				continue;
			if (y > R[0][x])
				continue;
			if (fn[0][x][1] < R[1][y])
				continue;
			if (fn[1][y][0] > L[0][x])
				continue;
			int oppx = max(fn[0][x][0], R[1][y]);
			int oppy = min(fn[1][y][1], L[0][x]);
			if (R[2][oppx] <= oppy) {
				vector<pi> points;
				points.push_back({xmin, x});
				points.push_back({y, ymax});
				points.push_back({xmax, oppx});
				points.push_back({oppy, ymin});
				for (auto &r : a) {
					bool ok = 0;
					for (auto &z : points)
						if (contain(r, z[0], z[0], z[1], z[1]))
							ok = 1;
					if (!ok)
						assert(0);
				}
				for (auto &[x, y] : points)
					cout << vx[x] << " " << vy[y] << "\n";
				return 0;
			}
		}
	}
}