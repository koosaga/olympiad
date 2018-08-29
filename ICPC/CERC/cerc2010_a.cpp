#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using frac = pair<lint, lint>;
const int MAXN = 10005;

struct point{
	lint x, y, z;
	point operator-(const point &p)const{
		return (point){x - p.x, y - p.y, z - p.z};
	}
	bool operator==(const point &p)const{
		return x == p.x && y == p.y && z == p.z;
	}
	point operator*(const point &b)const{
		return (point){
			y * b.z - b.y * z, 
			z * b.x - b.z * x, 
			x * b.y - b.x * y};
	}
}a[4];

bool cmp(const frac &a, const frac &b){ return 1ll * a.first * b.second < 1ll * b.first * a.second; }

lint dot(point a, point b){ return a.x * b.x + a.y * b.y + a.z * b.z; }
lint dist(point a, point b){ return dot(b - a, b - a); }
point plane(point a, point b, point c){ return (b - a) * (c - a); }

frac p2l(point a, point b, point c){
	if(b == c) return frac(dist(a, b), 1);
	if(dot(c - b, a - b) < 0) return frac(dist(a, b), 1);
	if(dot(b - c, a - c) < 0) return frac(dist(a, c), 1);
	return frac(dist((point){0, 0, 0}, (b - c) * (a - c)), dist(b, c));
}

frac point_tri(point a, point *b){
	frac ret = min({p2l(a, b[0], b[1]), p2l(a, b[1], b[2]), p2l(a, b[2], b[0])}, cmp);
	if(dot(plane(b[0], b[1], b[2]), a) < dot(plane(b[0], b[1], b[2]), b[0])){
		swap(b[1], b[2]);
	}
	point P = plane(b[0], b[1], b[2]);
	if(dot(P, P) == 0) return ret;
	if(ret.first == 0) return ret;
	if(dot(P, plane(b[0], a, b[1])) >= 0) return ret;
	if(dot(P, plane(b[1], a, b[2])) >= 0) return ret;
	if(dot(P, plane(b[2], a, b[0])) >= 0) return ret;
	frac vupy = frac(dot(P, a) - dot(P, b[0]), dist((point){0, 0, 0}, P));
	vupy.first *= vupy.first;
	ret = min(ret, vupy, cmp);
	return ret;
}

lint gcd(lint x, lint y){ return y ? gcd(y, x%y) : x; }

int main(){
	int t; scanf("%d",&t);
	while(t--){
		for(int i=0; i<4; i++){
			scanf("%lld %lld %lld",&a[i].x,&a[i].y,&a[i].z);
		}
		point p1 = a[2] - a[0];
		point p2 = a[3] - a[0];
		point p3 = a[2] - a[1];
		point p4 = a[3] - a[1];
		point a1[3] = {p1, p2, p3};
		point a2[3] = {p2, p3, p4};
		frac ans = min(point_tri((point){0, 0, 0}, a1), point_tri((point){0, 0, 0}, a2), cmp);
		lint g = gcd(ans.first, ans.second);
		ans.first /= g;
		ans.second /= g;
		printf("%lld %lld\n", ans.first, ans.second);
	}
}
