#include <bits/stdc++.h>
using namespace std;
const int MAXN = 16;
using real_t = double;
using pi = pair<real_t, real_t>;

int n, ret, r[MAXN];
pi s[MAXN], t[MAXN];
bool vis[1 << MAXN];

real_t dist(pi s, pi e){
	return hypot(e.first - s.first, e.second - s.second);
}

real_t ccw(pi a, pi b, pi c){
	real_t dx1 = b.first - a.first;
	real_t dy1 = b.second - a.second;
	real_t dx2 = c.first - a.first;
	real_t dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}
real_t dot(pi a, pi b, pi c){
	real_t dx1 = b.first - a.first;
	real_t dy1 = b.second - a.second;
	real_t dx2 = c.first - a.first;
	real_t dy2 = c.second - a.second;
	return dx1 * dx2 + dy1 * dy2;
}

double seg_to_point(pi s, pi e, pi x){
	if(dot(s, e, x) < 0) return dist(s, x);
	if(dot(e, s, x) < 0) return dist(e, x);
	return fabs(ccw(s, e, x)) / dist(s, e);
}

bool Collide(int c, pi cen, int rad){
	return seg_to_point(s[c], t[c], cen) <= rad; 
}

bool Move(int msk, int c){
	for(int i=0; i<n; i++){
		if(i != c){
			if((msk >> i) % 2 == 1 && Collide(c, t[i], r[i] + r[c])) return 0;
			if((msk >> i) % 2 == 0 && Collide(c, s[i], r[i] + r[c])) return 0;
		}
	}
	return 1;
}

void dfs(int msk, int d){
	ret = max(ret, d);
	vis[msk] = 1;
	for(int i=0; i<n; i++){
		if((msk >> i) & 1) continue;
		if(!vis[msk | (1 << i)] && Move(msk, i)){
			dfs(msk | (1 << i), d + 1);
		}
	}
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> r[i] >> s[i].first >> s[i].second >> t[i].first >> t[i].second;
	}
	dfs(0, 0);
	cout << ret << endl;
}