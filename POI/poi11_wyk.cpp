#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int mod = 1e9 + 7;
const double eps = 1e-1;

using Point = complex<double>;
struct Circle{ Point p; double r; };
double dot(Point p, Point q){ return p.real() * p.real() + p.imag() * p.imag(); }
double dist(Point p, Point q){ return dot(q - p, q - p); }
double area2(Point p, Point q){ return p.real() * q.imag() - q.real() * p.imag(); }
bool in(const Circle& c, Point p){ return dist(c.p, p) < c.r + eps; }
Circle INVAL = Circle{Point(0, 0), -1};
Circle mCC(Point a, Point b, Point c){
	b -= a; c -= a;
	double d = 2*area2(b, c); if(abs(d) < eps) return INVAL;
	Point ans = (c*dot(b, b) - b*dot(c, c)) * Point(0, -1) / d;
	return Circle{a + ans, dist(Point(0, 0), ans)};
}

mt19937 gen(0x94949); 

Circle solve(vector<Point> p){
	if(sz(p) == 1){
		return Circle{p[0], 0};
	}
	if(sz(p) == 2){
		return Circle{(p[0] + p[1]) / 2.0, dist(p[0], p[1]) / 4.0};
	}

	shuffle(p.begin(), p.end(), gen);
	Circle c = INVAL;
	for(int i=0; i<p.size(); ++i) if(c.r<0 ||!in(c, p[i])){
		c = Circle{p[i], 0};
		for(int j=0; j<=i; ++j) if(!in(c, p[j])){
			Circle ans{(p[i]+p[j])*0.5, dist(p[i], p[j])*0.25};
			if(c.r == 0) { c = ans; continue; }
			Circle l, r; l = r = INVAL;
			Point pq = p[j]-p[i];
			for(int k=0; k<=j; ++k) if(!in(ans, p[k])) {
				double a2 = area2(pq, p[k]-p[i]);
				Circle c = mCC(p[i], p[j], p[k]);
				if(c.r<0) continue;
                double b2 = area2(pq, c.p-p[i]) ;
				if(a2 > 0 && (l.r<0||b2 > area2(pq, l.p-p[i]))) l = c;
				else if(a2 < 0 && (r.r<0||b2 < area2(pq, r.p-p[i]))) r = c;
			}
			if(l.r<0&&r.r<0) c = ans;
			else if(l.r<0) c = r;
			else if(r.r<0) c = l;
			else c = l.r<=r.r?l:r;
		}
	}
	return c;
}

int n, m;
Point a[MAXN];

Circle cost(int l, int r){
	return solve(vector<Point>(a + l, a + r + 1));
}

vector<Circle> trace;

bool trial(double x){
	trace.clear();
	int cur = 0;
	for(int i=0; i<m; i++){
		int st = cur, ed = n - m + i;
		int p = 1;
		while(cur + p - 1 <= ed && cost(cur, cur + p - 1).r <= x) p <<= 1;
		ed = min(ed, cur + p - 1);
		st = cur + (p / 2) - 1;
		while(st != ed){
			int mid = (st + ed + 1) / 2;
			if(cost(cur, mid).r > x) ed = mid - 1;
			else st = mid;
		}
		trace.push_back(cost(cur, st));
		cur = st + 1;
	}
	return cur == n;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		int x = rand() % 2000001 - 1000000;
		int y = rand() % 2000001 - 1000000;
		scanf("%d %d",&x,&y);
		a[i] = Point(x, y);
	}
	double s = 0, e = 2e12;
	while(sqrt(e) - sqrt(s) > 5e-7){
		double mid = (s+e)/2;
		if(trial(mid)) e = mid;
		else s = mid;
	}
	trial(e);
	printf("%.10f\n", sqrt(e));
	printf("%d\n", sz(trace));
	for(auto &i : trace) printf("%.10f %.10f\n", i.p.real(), i.p.imag());
}
