#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;

/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
#pragma once

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};


template<class P>
int lineIntersection(const P& s1, const P& e1, const P& s2,
		const P& e2, P& r) {
	if ((e1-s1).cross(e2-s2)) { //if not parallell
		r = s2-(e2-s2)*(e1-s1).cross(s2-s1)/(e1-s1).cross(e2-s2);
		return 1;
	} else
		return -((e1-s1).cross(s2-s1)==0 || s2==e2);
}

const int P = 6e8;
const int INF = 1e9;
int main(){
	printf("%d %d\n%d %d\n%d %d\n%d %d\n", 
	-INF, INF - P,
	-INF + P + 1, INF,
	INF - P, -INF,
	INF, -INF + P - 1);
	Point<llf> P1(-INF, INF - P);
	Point<llf> P2(-INF + P + 1, INF); // (P + 1, P)
	Point<llf> P3(INF - P, -INF);
	Point<llf> P4(INF, -INF + P - 1); // (P, P - 1)
}
