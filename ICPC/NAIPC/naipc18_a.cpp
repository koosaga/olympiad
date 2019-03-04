#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using real_t = long double;
const int MAXN = 205;
const real_t inf = 1e12;
typedef pair<real_t, real_t> pi;

int n, m;
pi clo[MAXN], chi[MAXN];
pi insec[MAXN][MAXN];
pi a[MAXN], b[MAXN];

real_t dist(pi a, pi b){
	return hypot(b.first - a.first, b.second - a.second);
}

bool vis[MAXN][MAXN];
real_t mem[MAXN][MAXN];

int nxt(int x){ return (x + 1) % m; }

real_t DP(int s, int e){
	if(vis[s][e]) return mem[s][e];
	if(nxt(s) == e) return 0;
	real_t ans = inf;
	for(int i=nxt(s); i!=e; i=nxt(i)){
		real_t sub = DP(s, i) + DP(i, e) + dist(b[i], b[i+1]);
		if(dist(b[i], insec[s][i]) < dist(b[i+1], insec[s][i])){
			sub += min(dist(b[i], insec[s][i]), dist(b[i], clo[i]));
		}
		else sub += dist(b[i], clo[i]);
		if(dist(b[i+1], insec[i][e]) < dist(b[i], insec[i][e])){
			sub += min(dist(b[i+1], insec[i][e]), dist(b[i+1], chi[i]));
		}
		else sub += dist(b[i+1], chi[i]);
		ans = min(ans, sub);
	}
	vis[s][e] = 1;
	mem[s][e] = ans;
	return ans;
}


real_t ccw(pi a, pi b, pi c){
	real_t dx1 = b.first - a.first;
	real_t dy1 = b.second - a.second;
	real_t dx2 = c.first - a.first;
	real_t dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

pi line_line_intersection(pi A, pi B, pi C, pi D){
	real_t a = B.second - A.second;
	real_t b = A.first - B.first;
	real_t c = a * A.first + b * A.second;
	real_t d = D.second - C.second;
	real_t e = C.first - D.first;
	real_t f = d * C.first + e * C.second;
	real_t det = a * e - b * d;
	if(fabs(det) < 1e-1) return pi(inf, inf);
	return make_pair((c * e - f * b) / det, (a * f - c * d) / det);
}

int main(){
	cin >> n;
	for(int i=n-1; i>=0; i--){
		cin >> a[i].first >> a[i].second;
	}
	cin >> m;
	for(int i=m-1; i>=0; i--){
		cin >> b[i].first >> b[i].second;
	}
	b[m] = b[0];
	a[n] = a[0];
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(ccw(b[i], b[i+1], a[j]) < -0.5 && ccw(b[i], b[i+1], a[j+1]) > 0.5){
				chi[i] = line_line_intersection(b[i], b[i+1], a[j], a[j+1]);
			}
			if(ccw(b[i], b[i+1], a[j]) > 0.5 && ccw(b[i], b[i+1], a[j+1]) < -0.5){
				clo[i] = line_line_intersection(b[i], b[i+1], a[j], a[j+1]);
			}
		}
	}
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			if(i != j){
				insec[i][j] = line_line_intersection(b[i], b[i+1], b[j], b[j+1]);
			}
		}
	}
	real_t ans = inf;
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			if(i == j) continue;
			real_t tmp = DP(i, j) + DP(j, i);
			tmp += dist(chi[i], clo[i]);
			if(dist(b[j], insec[i][j]) < dist(b[j+1], insec[i][j])){
				tmp += dist(b[j], chi[j]);
				tmp += min(dist(b[j], insec[i][j]), dist(b[j], clo[j]));
			}
			else{
				tmp += dist(b[j+1], clo[j]);
				tmp += min(dist(b[j+1], insec[i][j]), dist(b[j+1], chi[j]));
			}
			ans = min(ans, tmp);
		}
	}
	printf("%.10Lf\n", ans);
}

