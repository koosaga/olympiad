#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
#define sz(v) ((int)(v).size())

struct vec3{
	llf x, y, z;
	vec3(): x(0), y(0), z(0) {}
	vec3(llf a, llf b, llf c): x(a), y(b), z(c) {}
	vec3 operator*(const vec3& v) const{ return vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	vec3 operator^(const vec3& v) const{ return vec3(x*v.x, y*v.y, z*v.z); }
	vec3 operator-(const vec3& v) const{ return vec3(x-v.x, y-v.y, z-v.z); }
	vec3 operator+(const vec3& v) const{ return vec3(x+v.x, y+v.y, z+v.z); }
	vec3 operator-() const{ return vec3(-x, -y, -z); }
	llf dot(const vec3 &v) const{ return x*v.x+y*v.y+z*v.z; }
};

struct face{
	vec3 norm;
	llf disc;
};

face make_face(int i, int j, int k, vector<vec3> &A){ // p^T * norm < disc
	face f;
	f.norm = (A[j]-A[i])*(A[k]-A[i]);
	f.disc = f.norm.dot(A[i]);
	return f;
}

struct kek{
	vec3 sum, sqsum;
	int cnt;
	void init(){
		cnt = 0;
		sum = vec3(0, 0,0 );
		sqsum = vec3(0, 0,0 );
	}
	void add_vect(vec3 v){
		sum = sum + v;
		sqsum = sqsum + (v^v) ;
		cnt++;
	}
	llf eval(){
		if(cnt <= 1) return 0;
		auto ans = sum ^ sum;
		llf ret = -(ans.x + ans.y + ans.z) / cnt;
		ret += sqsum.x + sqsum.y + sqsum.z;
		return ret;
	}
};

int main(){
	int n, k;
	cin >> n >> k;
	vector<vec3> v(n);
	for(int i=0; i<n; i++){
		cin >> v[i].x >> v[i].y >> v[i].z;
	}
	if(k == 1){
		kek tot; tot.init();
		for(auto &i : v) tot.add_vect(i);
		printf("%.6f\n", (double)tot.eval());
		return 0;
	}
	if(n <= 2){
		puts("0.000000");
		return 0;
	}
	llf ret = 1e18;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			for(int k=0; k<j; k++){
				auto fa = make_face(i, j, k, v);
				vector<vec3> brue;
				kek l, r;
				l.init(); r.init();
				for(int x = 0; x < n; x++){
					if(x == i || x == j || x == k){
						brue.push_back(v[x]);
					}
					else{
						lint val = fa.norm.dot(v[x]) - fa.disc;
						assert(val != 0);
						if(val > 0) l.add_vect(v[x]);
						else r.add_vect(v[x]);
					}
				}
				assert(sz(brue) == 3);
				for(int i=0; i<8; i++){
					kek nl = l;
					kek nr = r;
					for(int j=0; j<3; j++){
						if((i >> j) & 1) nl.add_vect(brue[j]);
						else nr.add_vect(brue[j]);
					}
					ret = min(ret, nl.eval() + nr.eval());
				}
			}
		}
	}
	printf("%.6f\n", (double)ret);
}
