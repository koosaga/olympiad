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
}a[61];
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

real_t getXcen(){
	vector<int> v;
	for(int i=0; i<n; i++){
		v.push_back(a[i].x);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	if(v.size() == 1) return v[0];
	real_t vol = 0;
	real_t xsum = 0;
	for(int i=0; i<v.size()-1; i++){
		real_t ar1 = get_insec(v[i]);
		real_t ar2 = get_insec(v[i] * 0.5 + v[i+1] * 0.5);
		real_t ar3 = get_insec(v[i+1]);
		{
			real_t trapez = ar1 + 4 * ar2 + ar3;
			trapez *= (v[i+1] - v[i]) / 6.0;
			vol += trapez;
		}
		{
			ar1 *= v[i];
			ar2 *= v[i] * 0.5 + v[i+1] * 0.5;
			ar3 *= v[i+1];
			real_t trapez = ar1 + 4 * ar2 + ar3;
			trapez *= (v[i+1] - v[i]) / 6.0;
			xsum += trapez;
		}
	}
	return xsum / vol;
}

real_t dist(vec3 a, vec3 b, vec3 c, real_t x, real_t y, real_t z){
	vec3 norm = (b - a) * (c - a);
	real_t dis = fabs(norm.dot(a) - norm.dot(x, y, z));
	dis /= norm.Sz();
	return dis;
}

real_t solve(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%lld %lld %lld",&a[i].x,&a[i].y,&a[i].z);
	}
	real_t p[3] = {};
	for(int i=0; i<3; i++){
		p[i] = getXcen();
		for(int j=0; j<n; j++){
			tie(a[j].x, a[j].y, a[j].z) = make_tuple(a[j].y, a[j].z, a[j].x);
		}
	}
//	printf("%.10f %.10f %.10f\n", p[0], p[1], p[2]);
	real_t ret = 1e9;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			for(int k=0; k<j; k++){
				vec3 norm = (a[j] - a[i]) * (a[k] - a[i]);
				lint disc = norm.dot(a[i]);
				lint minv = 1e18;
				lint maxv = -1e18;
				for(int l=0; l<n; l++){
					minv = min(minv, norm.dot(a[l]));
					maxv = max(maxv, norm.dot(a[l]));
				}
				if(minv < disc && disc < maxv) continue;
//				printf("see %d %d %d\n", i, j, k);
//				printf("dist = %.10f\n", dist(a[i], a[j], a[k], p[0], p[1], p[2]));
				ret = min(ret, dist(a[i], a[j], a[k], p[0], p[1], p[2]));
			}
		}
	}
	return ret;
}

int main(){
	real_t ret = 0;
	for(int i=0; i<2; i++){
		real_t ans = solve();
	//	printf("%.10f\n", (double)ans);
		ret += ans;
	}
	printf("%.10f\n", (double)ret);
}
