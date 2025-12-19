#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

pi operator-(pi a, pi b) { return pi{a[0] - b[0], a[1] - b[1]}; }
lint ccw(pi a, pi b) { return a[0] * b[1] - a[1] * b[0]; }
lint dot(pi a, pi b) { return a[0] * b[0] + a[1] * b[1]; }
lint ccw(pi a, pi b, pi c) { return ccw(b - a, c - a); }
lint dist(pi a, pi b) { return dot(b - a, b - a); }

bool inside(pi a, pi b, pi c) {
	if (a[0] > c[0])
		swap(a[0], c[0]);
	if (a[1] > c[1])
		swap(a[1], c[1]);
	return a[0] <= b[0] && b[0] <= c[0] && a[1] <= b[1] && b[1] <= c[1];
}

int sccw(pi a, pi b, pi c) {
	lint z = ccw(a, b, c);
	if (z != 0)
		return z > 0 ? 1 : -1;
	return 0;
}

bool cross(pi a, pi b, pi c, pi d) {
	if (sccw(a, b, c) == 0 && sccw(a, b, d) == 0) {
		return inside(a, c, b) || inside(a, d, b) || inside(c, a, d) || inside(c, b, d);
	}
	int c1 = sccw(a, b, c) * sccw(a, b, d);
	int c2 = sccw(c, d, a) * sccw(c, d, b);
	if (c1 <= 0 && c2 <= 0)
		return true;
	return false;
}

vector<pi> cvxh(vector<pi> P) {
	swap(P[0], *min_element(all(P)));
	sort(1 + all(P), [&](const pi &a, const pi &b) {
		lint z = ccw(P[0], a, b);
		if (z != 0)
			return z > 0;
		return dist(P[0], a) < dist(P[0], b);
	});
	vector<pi> H;
	for (auto &x : P) {
		while (sz(H) >= 2 && ccw(H[sz(H) - 2], H.back(), x) <= 0)
			H.pop_back();
		H.push_back(x);
	}
	return H;
}
// by zigui
// C : counter_clockwise(C[0] == C[N]), N >= 2
// return highest point in C <- P(clockwise) or -1 if strictly in convex
// recommend : strongly convex, C[i] != P

int convex_tangent(vector<pi> &C, pi P, int up = 1) {
	auto sign = [&](lint c) { return c > 0 ? up : c == 0 ? 0 : -up; };
	auto local = [&](pi P, pi a, pi b, pi c) { return sign(ccw(P, a, b)) <= 0 && sign(ccw(P, b, c)) >= 0; };
	int N = C.size() - 1, s = 0, e = N, m;
	if (local(P, C[1], C[0], C[N - 1]))
		return 0;
	while (s + 1 < e) {
		m = (s + e) / 2;
		if (local(P, C[m - 1], C[m], C[m + 1]))
			return m;
		if (sign(ccw(P, C[s], C[s + 1])) < 0) { // up
			if (sign(ccw(P, C[m], C[m + 1])) > 0)
				e = m;
			else if (sign(ccw(P, C[m], C[s])) > 0)
				s = m;
			else
				e = m;
		} else { // down
			if (sign(ccw(P, C[m], C[m + 1])) < 0)
				s = m;
			else if (sign(ccw(P, C[m], C[s])) < 0)
				s = m;
			else
				e = m;
		}
	}
	if (s && local(P, C[s - 1], C[s], C[s + 1]))
		return s;
	if (e != N && local(P, C[e - 1], C[e], C[e + 1]))
		return e;
	return -1;
}

bool in_seg(pi a, pi b, pi c) { return ccw(a, b, c) == 0 && inside(a, c, b); }

int Mod(int x, int m) { return (x % m + m) % m; }

vector<pi> Fast(vector<pi> P, vector<pi> H) {
	vector<pi> RH = H;
	for (auto &z : RH)
		z[0] *= -1;
	RH = cvxh(RH);
	{
		auto pp = H[0], qq = RH[0];
		H.push_back(pp);
		RH.push_back(qq);
	}
	vector<array<pi, 2>> intvs;
	for (auto &x : P) {
		int p1 = convex_tangent(H, x);
		int p2 = convex_tangent(RH, pi{-x[0], x[1]});
		assert(p1 != -1 && p2 != -1);
		pi V1 = H[p1] - x;
		pi V2 = RH[p2] - pi{-x[0], x[1]};
		V2[0] *= -1;
		assert(ccw(V1, V2) >= 0);
		V1 = pi{V1[1], -V1[0]};
		V2 = pi{-V2[1], V2[0]};
		swap(V1, V2);
		intvs.push_back({V1, V2});
	}
	vector<pi> points;
	for (auto &[x, y] : intvs) {
		points.push_back(x);
		points.push_back(y);
	}
	auto cmp = [&](const pi &a, const pi &b) {
		bool m1 = (a < pi{0, 0});
		bool m2 = (b < pi{0, 0});
		if (m1 != m2)
			return m1 < m2;
		return ccw(a, b) > 0;
	};
	sort(all(points), cmp);
	points.resize(unique(all(points),
						 [&](const pi &a, const pi &b) {
							 bool m1 = (a < pi{0, 0});
							 bool m2 = (b < pi{0, 0});
							 return m1 == m2 && ccw(a, b) == 0;
						 }) -
				  points.begin());
	vector<array<int, 3>> comps;
	for (int i = 0; i < sz(P); i++) {
		int i1 = lower_bound(all(points), intvs[i][0], cmp) - points.begin();
		int i2 = lower_bound(all(points), intvs[i][1], cmp) - points.begin();
		if (i1 > i2) {
			comps.push_back({i1, i2 + sz(points), i});
		} else {
			comps.push_back({i1, i2, i});
			comps.push_back({i1 + sz(points), i2 + sz(points), i});
		}
	}
	vector<pi> sfxMin(sz(points) * 2 + 1);
	fill(all(sfxMin), pi{int(1e9), -1});
	for (auto &[s, e, x] : comps) {
		sfxMin[s] = min(sfxMin[s], pi{e, x});
	}
	for (int i = sz(points) * 2 - 1; i >= 0; i--)
		sfxMin[i] = min(sfxMin[i], sfxMin[i + 1]);
	for (auto &[s, e, x] : comps) {
		auto j = sfxMin[e];
		if (j[0] - s <= sz(points)) {
			int y = j[1];
			for (int i = 0; i + 1 < sz(H); i++) {
				if (cross(H[i], H[i + 1], P[x], P[y])) {
					return vector<pi>{H[i], H[i + 1], P[x], P[y]};
				}
			}
			assert(0);
		}
	}
	return vector<pi>();
}

vector<pi> solve(vector<pi> P, vector<pi> Q) {
	auto PH = cvxh(P), QH = cvxh(Q);
	for (int i = 0; i < 2; i++) {
		vector<pi> Z = QH;
		Z.push_back(QH[0]);
		vector<pi> Pin, Pout;
		for (auto &x : P) {
			int q = convex_tangent(Z, x);
			if (q == -1) {
				Pin.push_back(x);
				continue;
			}
			for (int j = -2; j < 2; j++) {
				pi L = QH[Mod(q + j, sz(QH))];
				pi R = QH[Mod(q + j + 1, sz(QH))];
				if (in_seg(L, R, x)) {
					int q = find(all(P), x) - P.begin();
					return vector<pi>{L, R, x, P[Mod(q + 1, sz(P))]};
				}
			}
			Pout.push_back(x);
		}
		if (sz(Pin) && sz(Pout)) {
			for (int i = 0; i < sz(QH); i++) {
				if (cross(Z[i], Z[i + 1], Pin[0], Pout[0])) {
					return vector<pi>{Z[i], Z[i + 1], Pin[0], Pout[0]};
				}
			}
		}
		if (sz(Pin) == 0) {
			auto sol = Fast(Pout, QH);
			if (sz(sol) > 0)
				return sol;
		}
		swap(P, Q);
		swap(PH, QH);
	}
	return vector<pi>();
}

void sex(vector<pi> P, vector<pi> Q) {
	int n = sz(P), m = sz(Q);
	map<pi, int> fuck;
	for (int i = 0; i < n; i++) {
		fuck[P[i]] = i;
	}
	for (int i = 0; i < m; i++)
		fuck[Q[i]] = ~i;
	auto ans = solve(P, Q);
	if (sz(ans) == 0)
		cout << "-1\n";
	else {
		vector<int> d;
		for (int i = 0; i < 4; i++)
			d.push_back(fuck[ans[i]]);
		sort(all(d));
		d[0] = ~d[0];
		d[1] = ~d[1];
		assert(cross(P[d[2]], P[d[3]], Q[d[0]], Q[d[1]]));
		cout << d[2] + 1 << " " << d[3] + 1 << " " << d[0] + 1 << " " << d[1] + 1 << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); /*
	 while (true) {
		 int n = 10, m = 10;
		 set<pi> s;
		 while (sz(s) < n + m) {
			 int x = rand() % 20;
			 int y = rand() % 20;
			 s.insert({x, y});
		 }
		 vector<pi> QQ(all(s));
		 shuffle(all(QQ), mt19937_64(0x1557));
		 vector<pi> P(QQ.begin(), QQ.begin() + n);
		 vector<pi> Q(n + all(QQ));
		 sex(P, Q);
		 cout << "sucex" << endl;
	 }*/
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<pi> P(n);
		for (auto &[x, y] : P)
			cin >> x >> y;
		int m;
		cin >> m;
		vector<pi> Q(m);
		for (auto &[x, y] : Q)
			cin >> x >> y;
		sex(P, Q);
	}
}