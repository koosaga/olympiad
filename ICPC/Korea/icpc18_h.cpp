#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
const int MAXN = 20005;

int n;
struct line{
	pi a, b;
}a[MAXN];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

bool cross(pi p1, pi p2, pi p3, pi p4){
	if(ccw(p1, p2, p3) == 0 && ccw(p1, p2, p4) == 0){
		if(p1.first > p2.first) swap(p1.first, p2.first);
		if(p1.second > p2.second) swap(p1.second, p2.second);
		if(p3.first > p4.first) swap(p3.first, p4.first);
		if(p3.second > p4.second) swap(p3.second, p4.second);
		return max(p1.first, p2.first) <= min(p3.first, p4.first) && max(p1.second, p2.second) <= min(p3.second, p4.second);
	}
	auto n = [&](lint x){
		return (x ? (x > 0 ? 1 : -1) : 0);
	};
	return 
	n(ccw(p1, p2, p3)) * n(ccw(p1, p2, p4)) <= 0 &&
	n(ccw(p3, p4, p1)) * n(ccw(p3, p4, p2)) <= 0;
}

double dist(pi a, pi b){
	return hypot(b.first - a.first, b.second - a.second);
}

bool connect(pi x, pi y){
	for(int i=0; i<n; i++){
		if(a[i].a == x || a[i].b == x) continue;
		if(a[i].a == y || a[i].b == y) continue;
		if(cross(a[i].a, a[i].b, x, y)) return 0;
	}
	return 1;
}

double dp[MAXN][2];
double nxt[MAXN][2][2];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].a.first,&a[i].b.first,&a[i].b.second);
	}
	sort(a, a + n, [&](const line &x, const line &y){
		return x.a < y.a;
	});
	for(int i=0; i+1<n; i++){
		nxt[i][0][0] = dist(a[i].a, a[i+1].a);
		nxt[i][0][1] = dist(a[i].a, a[i+1].b);
		nxt[i][1][0] = dist(a[i].b, a[i+1].a);
		nxt[i][1][1] = dist(a[i].b, a[i+1].b);
	}
	auto send = [&](int x, line y){
		if(cross(a[x].a, a[x+1].b, y.a, y.b)) nxt[x][0][1] = 1e18;
		if(cross(a[x].b, a[x+1].a, y.a, y.b)) nxt[x][1][0] = 1e18;
		if(cross(a[x].b, a[x+1].b, y.a, y.b)) nxt[x][1][1] = 1e18;
	};
	vector<line> v;
	for(int i=0; i<n; i++){
		while(sz(v) && v.back().b.second < a[i].b.second){
			if(cross(v.back().a, v.back().b, a[i].a, a[i].b)){
				puts("-1");
				return 0;
			}
			if(a[i - 1].b != v.back().b) send(i - 1, v.back());
			v.pop_back();
		}
		v.push_back(a[i]);
	}
	v.clear();
	for(int i=n-1; i>=0; i--){
		while(sz(v) && v.back().b.second <= a[i].b.second){
			if(cross(v.back().a, v.back().b, a[i].a, a[i].b)){
				puts("-1");
				return 0;
			}
			if(a[i + 1].b != v.back().b) send(i, v.back());
			v.pop_back();
		}
		v.push_back(a[i]);
	}
	double dap = 1e18;
	for(int x = 0; x < 2; x++){
		for(int y = 0; y < 2; y++){
			if(x + y == 0) continue;
			auto ch1 = (x ? a[0].b : a[0].a);
			auto ch2 = (y ? a[n-1].b : a[n-1].a);
			if(!connect(ch1, ch2)) continue;
			for(int i=0; i<MAXN; i++) dp[i][0] = dp[i][1] = 1e18;
			dp[0][x] = 0;
			for(int i=0; i<n-1; i++){
				for(int j=0; j<2; j++){
					for(int k=0; k<2; k++){
						dp[i+1][k] = min(dp[i+1][k], dp[i][j] + nxt[i][j^1][k]);
					}
				}
			}
			double ret = dp[n-1][y^1];
			for(int i=0; i<n; i++) ret += dist(a[i].a, a[i].b);
			ret += dist(ch1, ch2);
			dap = min(dap, ret);
		}
	}
	if(dap > 1e17) puts("-1");
	else printf("%.1f\n", dap);
}
