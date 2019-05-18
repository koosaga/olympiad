
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using real_t = long double;
using ll = long long;
const real_t eps = 1e-7;
typedef pair<real_t, real_t> pi;
#define sz(v) int((v).size())

struct vec3{
	ll x, y, z;
	vec3(): x(0), y(0), z(0) {}
	vec3(ll a, ll b, ll c): x(a), y(b), z(c) {}
	vec3 operator*(const vec3& v) const{ return vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	vec3 operator-(const vec3& v) const{ return vec3(x-v.x, y-v.y, z-v.z); }
	vec3 operator-() const{ return vec3(-x, -y, -z); }
	ll dot(const vec3 &v) const{ return x*v.x+y*v.y+z*v.z; }
	real_t dot(real_t vx, real_t vy, real_t vz) const{ return x*vx+y*vy+z*vz; }
	real_t Sz(){
		return sqrt(x * x + y * y + z * z);
	}
}a[111];
int n;

real_t get_insec(real_t x){
	vector<pi> p;
	for(int i=0; i<n; i++){
		if(fabs(a[i].x - x) < eps){
			p.emplace_back(1.0 * a[i].y, 1.0 * a[i].z);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(a[i].x < x - eps && a[j].x > x + eps){
				real_t rt = (x - a[i].x) / (a[j].x - a[i].x);
				real_t py = a[i].y + rt * (a[j].y - a[i].y);
				real_t pz = a[i].z + rt * (a[j].z - a[i].z);
				p.emplace_back(py, pz);
			}
		}
	}
	auto ccw = [&](pi a, pi b, pi c){
		real_t dx1 = b.first - a.first;
		real_t dy1 = b.second - a.second;
		real_t dx2 = c.first - a.first;
		real_t dy2 = c.second - a.second;
		return dx1 * dy2 - dy1 * dx2;
	};
	auto dist = [&](pi a, pi b){
		real_t dx = b.first - a.first;
		real_t dy = b.second - a.second;
		return dx *dx + dy * dy;
	};
	vector<pi> q;
	for(auto &i : p){
		bool good = 1;
		for(auto &j : q){
			if(dist(i, j) < eps){
				good = 0;
			}
		}
		if(good) q.push_back(i);
	}
	p = q;
	if(p.empty()) return 0;
	swap(p[0], *min_element(p.begin(), p.end()));
	sort(p.begin() + 1, p.end(), [&](const pi &a, const pi &b){
		real_t x = ccw(p[0], a, b);
		if(fabs(x) < eps) return dist(p[0], a) < dist(p[0], b);
		return x > 0;
	});
	vector<pi> h;
	for(auto &i : p){
		while(h.size() >= 2 && ccw(h[h.size()-2], h.back(), i) <= 0){
			h.pop_back();
		}
		h.push_back(i);
	}
	real_t ret = 0;
	for(int i=1; i<h.size(); i++){
		ret += ccw(h[0], h[i-1], h[i]);
	}
	return ret;
}


int main(){
	freopen("aerodynamics.in", "r", stdin);
	freopen("aerodynamics.out", "w", stdout);
	int qs, qe;
	scanf("%d %d %d",&n,&qs,&qe);
	for(int i=0; i<n; i++){
		scanf("%lld %lld %lld",&a[i].z,&a[i].y,&a[i].x);
	}
	for(int i=qs; i<=qe; i++) printf("%.10Lf\n", 0.5 * get_insec(i));
}

