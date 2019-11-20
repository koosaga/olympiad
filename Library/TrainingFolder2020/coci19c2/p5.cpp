#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = __int128;
using pi = pair<lint, lint>;
const int MAXN = 100005;

lint ccw(pi a, pi b, pi c){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int convex_tangent(vector<pi> &C, pi P, int up = 1){
	auto sign = [&](lint c){ return c > 0 ? up : c == 0 ? 0 : -up; };
	auto local = [&](pi P, pi a, pi b, pi c) {
		return sign(ccw(P, a, b)) <= 0 && sign(ccw(P, b, c)) >= 0;
	};
	int N = C.size()-1, s = 0, e = N, m;
	if( local(P, C[1], C[0], C[N-1]) ) return 0;
	while(s+1 < e){
		m = (s+e) / 2;
		if( local(P, C[m-1], C[m], C[m+1]) ) return m;
		if( sign(ccw(P, C[s], C[s+1])) < 0){ // up
			if( sign(ccw(P, C[m], C[m+1])) > 0) e = m;
			else if( sign(ccw(P, C[m], C[s])) > 0) s = m;
			else e = m;
		}
		else{ // down
			if( sign(ccw(P, C[m], C[m+1])) < 0) s = m;
			else if( sign(ccw(P, C[m], C[s])) < 0) s = m;
			else e = m;
		}
	}
	if( s && local(P, C[s-1], C[s], C[s+1]) ) return s;
	if( e != N && local(P, C[e-1], C[e], C[e+1]) ) return e;
	return -1;
}

bool query(vector<pi> &a, pi x){
	int n = sz(a) - 1;
	int x1 = convex_tangent(a, x, -1);
	int x2 = convex_tangent(a, x, 1);
	if(x1 == -1 || x2 == -1) return 1;
	int l = (x2 - x1 + n) % n;
	if(l <= n / 2 - 1) return 1;
	return 0;
}

int main(){
	int t, n;
	scanf("%d %d",&t,&n);
	vector<pi> a(n);
	for(int i=0; i<n; i++){
		long long x, y; scanf("%lld %lld",&x,&y);
		a[i] = pi(x, y);
	}
	a.push_back(a[0]);
	int q; scanf("%d",&q);
	long long lst = 0;
	while(q--){
		long long x, y; scanf("%lld %lld",&x,&y);
		x ^= (t * lst * lst * lst);
		y ^= (t * lst * lst * lst);
		bool ans = query(a, pi(x, y));
		puts(ans ? "DA" : "NE");
		lst += ans;
	}
}
