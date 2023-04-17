#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using real_t = long double;
const real_t eps = 1e-9;
const real_t MAXLEN = 2000;

template <class T> struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	P operator*(T d) const { return P(x * d, y * d); }
	P operator/(T d) const { return P(x / d, y / d); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this / dist(); } // makes dist()=1
	P perp() const { return P(-y, x); }		  // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const { return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};

template <class P> int lineIntersection(const P &s1, const P &e1, const P &s2, const P &e2, P &r) {
	if ((e1 - s1).cross(e2 - s2)) { // if not parallell
		r = s2 - (e2 - s2) * (e1 - s1).cross(s2 - s1) / (e1 - s1).cross(e2 - s2);
		return 1;
	} else
		return -((e1 - s1).cross(s2 - s1) == 0 || s2 == e2);
}

template <class P> int segmentIntersection(const P &s1, const P &e1, const P &s2, const P &e2, P &r1, P &r2) {
	if (e1 == s1) {
		if (e2 == s2) {
			if (e1 == e2) {
				r1 = e1;
				return 1;
			} // all equal
			else
				return 0; // different point segments
		} else
			return segmentIntersection(s2, e2, s1, e1, r1, r2); // swap
	}
	// segment directions and separation
	P v1 = e1 - s1, v2 = e2 - s2, d = s2 - s1;
	auto a = v1.cross(v2), a1 = v1.cross(d), a2 = v2.cross(d);
	if (a == 0) { // if parallel
		auto b1 = s1.dot(v1), c1 = e1.dot(v1), b2 = s2.dot(v1), c2 = e2.dot(v1);
		if (a1 || a2 || max(b1, min(b2, c2)) > min(c1, max(b2, c2)))
			return 0;
		r1 = min(b2, c2) < b1 ? s1 : (b2 < c2 ? s2 : e2);
		r2 = max(b2, c2) > c1 ? e1 : (b2 > c2 ? s2 : e2);
		return 2 - (r1 == r2);
	}
	if (a < 0) {
		a = -a;
		a1 = -a1;
		a2 = -a2;
	}
	if (eps < a1 || a < -a1 - eps || eps < a2 || a < -a2 - eps)
		return 0;
	r1 = s1 - v1 * a2 / a;
	return 1;
}

template <class P> real_t segDist(P &s, P &e, P &p) {
	if (s == e)
		return (p - s).dist();
	auto d = (e - s).dist2(), t = min(d, max(.0L, (p - s).dot(e - s)));
	return ((p - s) * d - (e - s) * t).dist() / d;
}

using point = Point<real_t>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<point> a(n + 2);
	// 0 ~ n-1 : polygon
	// n : guard
	// n+1 : sculpture
	// n+2 ~ : auxiliary points
	for (int i = 0; i < n + 2; i++) {
		cin >> a[i].x >> a[i].y;
	}
	for (int i = 0; i < n + 1; i++) {
		point A = a[n + 1], B = a[i] - a[n + 1]; // A -> B
		B = B / B.dist();
		vector<pair<real_t, int>> event;
		for (int j = 0; j < n; j++) {
			point C = a[j], D = a[(j + 1) % n];
			point i1, i2;
			int ret = segmentIntersection(A, A + B * MAXLEN, C, D, i1, i2);
			if (ret) {
				if (ret == 2 && (i1 - A).dist() > (i2 - A).dist())
					swap(i1, i2);
				real_t dist = (i1 - A).dist();
				int blocks = 0;
				real_t ccw1 = (C - A).cross(B), ccw2 = (D - A).cross(B);
				if (min(ccw1, ccw2) < -eps)
					blocks |= 1;
				if (max(ccw1, ccw2) > eps)
					blocks |= 2;
				event.push_back({dist, blocks});
			}
		}
		double maxd = 0;
		{
			sort(all(event));
			int cur = 0;
			for (auto &[d, i] : event) {
				cur |= i;
				if (cur == 3) {
					maxd = d;
					break;
				}
			}
		}
		a.push_back(A + B * maxd);
		//	cout << setprecision(69) << a.back().x << " " << a.back().y << " "
		//		 << "case 1 " << i << endl;

		for (int j = 0; j <= n; j++) {
			point D = B.rotate(acos(-1) / 2);
			point i1, i2;
			if (segmentIntersection(A + B * eps, A + B * (maxd - eps), a[j] - D * MAXLEN, a[j] + D * MAXLEN, i1, i2)) {
				a.push_back(i1);
				//		cout << setprecision(69) << i1.x << " " << i1.y << " "
				//			 << "case 2 " << j << endl;
			}
		}
	}
	auto in_polygon = [&](point p) {
		point q = p + point{6974, 1557};
		point i1, i2;
		int ret = 0;
		for (int i = 0; i < n; i++) {
			if (segmentIntersection(p, q, a[i], a[(i + 1) % n], i1, i2))
				ret++;
		}
		return ret % 2;
	};
	auto in_seg = [&](point a, point b, point c) {
		auto norm = (b - a) / (b - a).dist();
		real_t crs = norm.cross(c - a);
		real_t dot = norm.dot(c - a);
		return abs(crs) < eps && dot > -eps && dot < (b - a).dist() + eps;
	};
	vector<real_t> dist(sz(a), 1e8);
	vector<int> vis(sz(a));
	dist[n] = 0;
	while (true) {
		double cur = 1e9;
		int v = -1;
		for (int i = 0; i < sz(a); i++) {
			if (!vis[i] && dist[i] < cur) {
				cur = dist[i];
				v = i;
			}
		}
		vis[v] = 1;
		if (v >= n + 1) {
			cout << setprecision(69) << cur << endl;
			return 0;
		}
		for (int w = 0; w < sz(a); w++) {
			if (vis[w])
				continue;
			double d = (a[w] - a[v]).dist();
			auto can_update = [&]() {
				if (d < eps)
					return true;
				if (v < n && in_seg(a[v], a[(v + 1) % n], a[w]))
					return true;
				if (v < n && in_seg(a[v], a[(v + n - 1) % n], a[w]))
					return true;
				point A = a[v], B = (a[w] - a[v]) / d;
				for (int i = 0; i < n; i++) {
					point i1, i2;
					int ret = segmentIntersection(a[v], a[w], a[i], a[(i + 1) % n], i1, i2);
					if (ret) {
						real_t dist = (i1 - A).dist();
						if (dist > eps && dist < d - eps)
							return false;
					}
				}
				if (!in_polygon((a[v] + a[w]) * 0.5L))
					return false;
				return true;
			};
			if (can_update()) {
				//		cout << v << " " << w << endl;
				dist[w] = min(dist[w], dist[v] + d);
			}
		}
	}
}