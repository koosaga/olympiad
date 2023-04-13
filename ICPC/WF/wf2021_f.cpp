#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

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

typedef Point<double> P;
double segDist(P &s, P &e, P &p) {
	if (s == e)
		return (p - s).dist();
	auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
	return ((p - s) * d - (e - s) * t).dist() / d;
}

template <class P> bool onSegment(const P &s, const P &e, const P &p) {
	P ds = p - s, de = p - e;
	return ds.cross(de) == 0 && ds.dot(de) <= 0;
}

template <class It, class P> bool insidePolygon(It begin, It end, const P &p, bool strict = true) {
	int n = 0; // number of isects with line from p to (inf,p.y)
	for (It i = begin, j = end - 1; i != end; j = i++) {
		// if p is on edge of polygon
		if (onSegment(*i, *j, p))
			return !strict;
		// or: if (segDist(*i, *j, p) <= epsilon) return !strict;
		// increment n if segment intersects line from p
		n += (max(i->y, j->y) > p.y && min(i->y, j->y) <= p.y && ((*j - *i).cross(p - *i) > 0) == (i->y <= p.y));
	}
	return n & 1; // inside if odd number of intersections
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pi>> poly(n);
	for (int i = 0; i < n; i++) {
		int v;
		cin >> v;
		poly[i].resize(v);
		for (auto &[x, y] : poly[i])
			cin >> x >> y;
	}
	vector<array<int, 3>> p1(m), p2(m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> p1[i][j];
		}
		for (int j = 0; j < 3; j++) {
			cin >> p2[i][j];
		}
	}
	auto trial = [&](double x) {
		vector<int> chk(n);
		for (int i = 0; i < m; i++) {
			double dx = p1[i][1] - p2[i][1];
			double dy = p2[i][0] - p1[i][0];
			double h = hypot(dx, dy);
			P f1(p1[i][0], p1[i][1]);
			P f2(p2[i][0], p2[i][1]);
			P dir(dx / h, dy / h);
			vector<P> rect;
			rect.push_back(f1 - dir * tan(x) * p1[i][2]);
			rect.push_back(f2 - dir * tan(x) * p2[i][2]);
			rect.push_back(f2 + dir * tan(x) * p2[i][2]);
			rect.push_back(f1 + dir * tan(x) * p1[i][2]);
			for (int j = 0; j < n; j++) {
				bool bad = 0;
				for (auto &[kx, ky] : poly[j]) {
					P p(kx, ky);
					if (!insidePolygon(rect.begin(), rect.end(), p)) {
						bad = 1;
						break;
					}
				}
				if (!bad)
					chk[j] = 1;
			}
		}
		return count(all(chk), 1) == n;
	};
	double s = 0, e = acos(-1) / 2;
	for (int i = 0; i < 69; i++) {
		double m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m;
	}
	if (s > acos(-1) / 2 - 1e-10)
		cout << "impossible\n";
	else
		cout << setprecision(69) << ((s + e) / 2) * (180 / acos(-1)) << "\n";
}