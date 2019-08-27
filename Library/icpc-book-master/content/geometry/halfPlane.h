/**
 * Author: xyz
 * Description: Halfplane intersection area
 */

#include "Point.h"
#include "lineIntersection.h"

#define eps 1e-8
typedef Point<double> P;

struct Line {
	P P1, P2;
	// Right hand side of the ray P1 -> P2
	explicit Line(P a = P(), P b = P()) : P1(a), P2(b) {};
	P intpo(Line y) {
		P r;
		assert(lineIntersection(P1, P2, y.P1, y.P2, r) == 1);
		return r;
	}
	P dir() {
		return P2 - P1;
	}
	bool contains(P x) {
		return (P2 - P1).cross(x - P1) < eps;
	}
	bool out(P x) {
		return !contains(x);
	}
}; 

template<class T>
bool mycmp(Point<T> a, Point<T> b) {
	// return atan2(a.y, a.x) < atan2(b.y, b.x);
	if (a.x * b.x < 0)	return a.x < 0;
	if (abs(a.x) < eps) {
		if (abs(b.x) < eps) 	return a.y > 0 && b.y < 0;
		if (b.x < 0)	return a.y > 0;
		if (b.x > 0)	return true;
	}
	if (abs(b.x) < eps) {
		if (a.x < 0)	return b.y < 0;
		if (a.x > 0)	return false;
	}
	return a.cross(b) > 0;
}

bool cmp(Line a, Line b) {
	return mycmp(a.dir(), b.dir());
}

double Intersection_Area(vector <Line> b) {
	sort(b.begin(), b.end(), cmp);
	int n = b.size();
	int q = 1, h = 0, i;
	vector <Line> c(b.size() + 10);
	for (i = 0; i < n; i++) {
		while (q < h && b[i].out(c[h].intpo(c[h - 1])))	h--;
		while (q < h && b[i].out(c[q].intpo(c[q + 1])))	q++;
		c[++h] = b[i];
		if (q < h && abs(c[h].dir().cross(c[h - 1].dir())) < eps) {
			if (c[h].dir().dot(c[h - 1].dir()) > 0) {
				h--;
				if (b[i].out(c[h].P1))	c[h] = b[i];
			}else {
				// The area is either 0 or infinite.
				// If you have a bounding box, then the area is definitely 0. 
				return 0;
			}
		}
	}
	while (q < h - 1 && c[q].out(c[h].intpo(c[h - 1])))	h--;
	while (q < h - 1 && c[h].out(c[q].intpo(c[q + 1])))	q++;
	// Intersection is empty. This is sometimes different from the case when
	// the intersection area is 0. 
	if (h - q <= 1)	return 0;
	c[h + 1] = c[q];
	vector <P> s;
	for (i = q; i <= h; i++)	s.push_back(c[i].intpo(c[i + 1]));
	s.push_back(s[0]);
	double ans = 0;
	for (i = 0; i < (int) s.size() - 1; i++)	ans += s[i].cross(s[i + 1]);
	return ans / 2;
}
