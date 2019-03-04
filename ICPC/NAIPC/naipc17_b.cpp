#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<double, double> pi;
const int MAXN = 1005;
typedef long long ll;

double ccw(pi a, pi b, pi c){
	double dx1 = b.first - a.first;
	double dy1 = b.second - a.second;
	double dx2 = c.first - a.first;
	double dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

double eps = 1e-9;
using Point = complex<double>;
struct Circle{ Point p; double r; };
double dist(Point p, Point q){ return abs(p-q); }
double area2(Point p, Point q){ return (conj(p)*q).imag();}
bool in(const Circle& c, Point p){ return dist(c.p, p) < c.r + eps; }
Circle INVAL = Circle{Point(0, 0), -1};
Circle mCC(Point a, Point b, Point c){
	b -= a; c -= a; 
	double d = 2*(conj(b)*c).imag(); if(abs(d)<eps) return INVAL;
	Point ans = (c*norm(b) - b*norm(c)) * Point(0, -1) / d;
	return Circle{a + ans, abs(ans)};
}
Circle enclosing_circle(vector<Point> p) {
	mt19937 gen(0x94949); shuffle(p.begin(), p.end(), gen);
	Circle c = INVAL;
	for(int i=0; i<p.size(); ++i) if(c.r<0 ||!in(c, p[i])){
		c = Circle{p[i], 0};
		for(int j=0; j<=i; ++j) if(!in(c, p[j])){
			Circle ans{(p[i]+p[j])*0.5, dist(p[i], p[j])*0.5};
			if(c.r == 0) {c = ans; continue;}
			Circle l, r; l = r = INVAL;
			Point pq = p[j]-p[i];
			for(int k=0; k<=j; ++k) if(!in(ans, p[k])) {
				double a2 = area2(pq, p[k]-p[i]);
				Circle c = mCC(p[i], p[j], p[k]);
				if(c.r<0) continue;
				else if(a2 > 0 && (l.r<0||area2(pq, c.p-p[i]) > area2(pq, l.p-p[i]))) l = c;
				else if(a2 < 0 && (r.r<0||area2(pq, c.p-p[i]) < area2(pq, r.p-p[i]))) r = c;
			}

			if(l.r<0&&r.r<0) c = ans;
			else if(l.r<0) c = r;
			else if(r.r<0) c = l;
			else c = l.r<=r.r?l:r;
		}
	}
	return c;
}

// code credit : https://gist.github.com/msg555/4963794

struct vec3{
	ll x, y, z;
	vec3(): x(0), y(0), z(0) {}
	vec3(ll a, ll b, ll c): x(a), y(b), z(c) {}
	vec3 operator*(const vec3& v) const{ return vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	vec3 operator-(const vec3& v) const{ return vec3(x-v.x, y-v.y, z-v.z); }
	vec3 operator-() const{ return vec3(-x, -y, -z); }
	ll dot(const vec3 &v) const{ return x*v.x+y*v.y+z*v.z; }
};

struct twoset {
	int a, b;
	void insert(int x) { (a == -1 ? a : b) = x; }
	bool contains(int x) { return a == x || b == x; }
	void erase(int x) { (a == x ? a : b) = -1; }
	int size() { return (a != -1) + (b != -1); }
} E[MAXN][MAXN]; // i < j

struct face{ 
	vec3 norm;
	ll disc;
	int I[3];
};

face make_face(int i, int j, int k, int ii, vector<vec3> &A){ // p^T * norm < disc
	E[i][j].insert(k); E[i][k].insert(j); E[j][k].insert(i);
	face f; f.I[0]=i, f.I[1]=j, f.I[2]=k;
	f.norm = (A[j]-A[i])*(A[k]-A[i]);
	f.disc = f.norm.dot(A[i]);
	if(f.norm.dot(A[ii])>f.disc){
		f.norm = -f.norm;
		f.disc = -f.disc;
	}
	return f;
}
vector<face> get_hull(vector<vec3> &A){
	int N = A.size();
	vector<face> faces; memset(E, -1, sizeof(E));
	faces.push_back(make_face(0,1,2,3,A));
	faces.push_back(make_face(0,1,3,2,A));
	faces.push_back(make_face(0,2,3,1,A));
	faces.push_back(make_face(1,2,3,0,A));
	for(int i=4; i<N; ++i){
		for(int j=0; j<faces.size(); ++j){
			face f = faces[j];
			if(f.norm.dot(A[i])>f.disc){
				E[f.I[0]][f.I[1]].erase(f.I[2]);
				E[f.I[0]][f.I[2]].erase(f.I[1]);
				E[f.I[1]][f.I[2]].erase(f.I[0]);
				faces[j--] = faces.back();
				faces.pop_back();
			}
		}
		int nf = faces.size();
		for(int j=0; j<nf; ++j){
			face f=faces[j];
			for(int a=0; a<3; ++a) for(int b=a+1; b<3; ++b){
				int c=3-a-b;
				if(E[f.I[a]][f.I[b]].size()==2) continue;
				faces.push_back(make_face(f.I[a], f.I[b], i, f.I[c], A));
			}
		}
	}
	return faces;
}

#define proj fuck

double proj(vec3 x, vec3 v){
	double xv = 1.0 * x.x * v.x + 1.0 * x.y * v.y + 1.0 * x.z * v.z;
	double vv = 1.0 * v.x * v.x + 1.0 * v.y * v.y + 1.0 * v.z * v.z;
	return xv / sqrt(vv);
}

int main(){
	int n;
	scanf("%d",&n);
	vector<vec3> v(n);
	for(auto &i : v) scanf("%lld %lld %lld",&i.x,&i.y,&i.z);
	auto ret = get_hull(v);
	double ans = 1e18;
	for(auto &i : ret){
		double minv = 1e9, maxv = -1e9;
		for(auto &j : v){
			double arg = j.dot(i.norm);
			minv = min(minv, arg);
			maxv = max(maxv, arg);
		}
		double h = (maxv - minv) / sqrt(i.norm.dot(i.norm));
		vec3 dirx;
		if(i.norm.x || i.norm.y){
			dirx = (vec3){-i.norm.y, i.norm.x, 0};
		}
		else{
			dirx = (vec3){0, -i.norm.z, i.norm.y};
		}
		vec3 diry = i.norm * dirx;
		vector<Point> w;
		for(auto &j : v){
			w.push_back(Point(proj(j, dirx), proj(j, diry)));
		}
		double rad = enclosing_circle(w).r; 
		ans = min(ans, M_PI * rad * rad * h);
	}
	printf("%.10f\n", ans);
}
