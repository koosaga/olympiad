#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

using real_t = long double;

vector<int> bn[MAXN];
int n, m, mxp[MAXN];
pi a[MAXN];

struct line{
	pi s, e;
	pi angle(){
		return pi(e.first - s.first, e.second - s.second);
	}
};

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

pair<real_t, real_t> crs(line x, line y){
	int a = x.e.second - x.s.second;
	int b = x.s.first - x.e.first;
	lint c = 1ll * a * x.s.first + 1ll * b * x.s.second;
	int d = y.e.second - y.s.second;
	int e = y.s.first - y.e.first;
	lint f = 1ll * d * y.s.first + 1ll * e * y.s.second;
	lint det = 1ll * a * e - 1ll * b * d;
	return make_pair((real_t)(e * c - b * f) / det, (real_t)(a * f - c * d) / det);
}

real_t ccw(pi a, pi b, pair<real_t, real_t> c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	real_t dx2 = c.first - a.first;
	real_t dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

vector<line> v;

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		bn[s].push_back(e);
	}
	int cur = 0;
	for(int i=1; i<n; i++){
		sort(bn[i].rbegin(), bn[i].rend());
		mxp[i] = n;
		for(auto &j : bn[i]){
			if(j == mxp[i]) mxp[i]--;
		}
		if(cur < mxp[i]){
			cur = mxp[i];
			v.push_back({a[i], a[mxp[i]]});
		}
	}
	vector<line> stk;
	for(int i=0; i<v.size(); i++){
		while(stk.size() >= 2 
				&& ccw(pi(0, 0), stk[stk.size()-2].angle(), v[i].angle()) < 0
				 && ccw(stk.back().s, stk.back().e, crs(v[i], stk[stk.size()-2])) < 0){
			stk.pop_back();
		}
		stk.push_back(v[i]);
	}
	vector<pair<real_t, real_t>> ret;
	ret.emplace_back(a[1].first, a[1].second);
	for(int i=1; i<stk.size(); i++) ret.push_back(crs(stk[i-1], stk[i]));
	ret.emplace_back(a[n].first, a[n].second);
	real_t ans = 0;
	for(int i=1; i<ret.size(); i++){
		real_t dx = ret[i-1].first - ret[i].first;
		real_t dy = ret[i-1].second - ret[i].second;
		real_t sqr = dx * dx + dy * dy;
		ans += sqrt((long double)sqr);
	}
	printf("%.10Lf\n",(long double)ans);
}


