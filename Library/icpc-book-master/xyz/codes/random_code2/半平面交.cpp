#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define eps 1e-8
struct Point {
	double x, y;
	Point() {
	}
	Point (double _x, double _y) {
		x = _x; y = _y;
	}
	double cross(Point p) {
		return x * p.y - y * p.x;
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	void write() {
		printf("%lf %lf\n", x, y);
	}
}a[2000], s[2000];

struct Line {
	double x1, y1, x2, y2;
	Line() {
	}
	Line(Point a, Point b) {
		x1 = a.x; y1 = a.y; x2 = b.x; y2 = b.y;
	}
	double angle() {
		return (y2 - y1) / (x2 - x1);
	}
	Point intpo(Line y) {
		double A = y2 - y1, B = x1 - x2, C = y1 * x2 - x1 * y2, a = y.y2 - y.y1, b = y.x1 - y.x2, c = y.y1 * y.x2 - y.x1 * y.y2;
		return Point((C * b - c * B) / (a * B - A * b), (C * a - c * A) / (A * b - a * B));
	}
	Point trans() {
		return Point(x2 - x1, y2 - y1);
	}
	bool out(Point x) {
		return Point(x2 - x1, y2 - y1).cross(Point(x.x - x1, x.y - y1)) > eps;
	}
	void write() {
		printf("%lf %lf %lf %lf\n", x1, y1, x2, y2);
	}
	void write1() {
		Point(x2 - x1, y2 - y1).write();
	}
}b[1500], c[1500];
int n, i, S, len;
double sum;

bool operator < (Point a, Point b) {
	if (a.x * b.x < 0)	return a.x < 0;
	if (a.x == 0) {
		if (b.x == 0) 	return a.y > 0 && b.y < 0;
		if (b.x < 0)	return a.y > 0;
		if (b.x > 0)	return true;
	}
	if (b.x == 0) {
		if (a.x < 0)	return b.y < 0;
		if (a.x > 0)	return false;
	}
	return a.cross(b) > 0;
}

bool cmp(Line a, Line b) {
	return a.trans() < b.trans();
}

double getit() {
	int q = 1, h = 0, i;
	double ans = 0;
	for (i = 1; i <= n; i++) {
		while (q < h && b[i].out(c[h].intpo(c[h - 1])))	h--;//这两个不能换位置。。
		while (q < h && b[i].out(c[q].intpo(c[q + 1])))	q++;
		c[++h] = b[i];
		if (q < h && abs(c[h].trans().cross(c[h - 1].trans())) < eps) {
			h--;
			if (b[i].out(Point(c[h].x1, c[h].y1)))	c[h] = b[i];
		}
	}
	while (q < h - 1 && c[q].out(c[h].intpo(c[h - 1])))	h--;//似乎也不能换
	while (q < h - 1 && c[h].out(c[q].intpo(c[q + 1])))	q++;
	if (h - q <= 1)	return 0;
	c[h + 1] = c[q];
	for (len = 0, i = q; i <= h; i++)	s[++len] = c[i].intpo(c[i + 1]);
	s[len + 1] = s[1];
	for (i = 1; i <= len; i++)	ans += s[i].cross(s[i + 1]);
	return ans / 2;
}

int main() {
	scanf("%d", &S);
	while (S--) {
		scanf("%d", &n);
		for (i = 1; i <= n; i++)	a[i].read();
		a[n + 1] = a[1];
		for (i = 1; i <= n; i++)	sum += a[i].cross(a[i + 1]);
		if (sum > 0) {
			for (i = 1; i * 2 <= n; i++)	swap(a[i], a[n - i + 1]);
			a[n + 1] = a[1];
		}
		
		for (i = 1; i <= n; i++)	b[i] = Line(a[i], a[i + 1]);
		
		sort(b + 1, b + n + 1, cmp);
		
		printf("%.2lf\n", getit() + eps);
	}
}